#pragma once

#include <memory>
#include <string>
#include <vector>


namespace Tau
{
	class None;
	class Boolean;
	class Number;

	class Exception
	{
		// TODO
	};

	class Object
	{
		friend Boolean;
		friend Number;
	protected:
		class Exception:
			public Tau::Exception
		{
			// TODO
		};
		class NotImplementedException:
			public Exception
		{
			// TODO
		};
	protected:
		class Proxy
		{
		public:
			class Empty;
		public:
			inline Proxy() = default;
			inline Proxy(const Proxy&) = delete;
			inline virtual ~Proxy() = default;
		public:
			inline Proxy& operator = (const Proxy&) = delete;
		public:
			inline virtual Object operator [] (const Object& key_) const = 0;
			inline virtual Object& operator [] (const Object& key_) = 0;
		public:
			inline virtual operator std::nullptr_t() const = 0;
			inline virtual operator bool() const = 0;
			inline virtual operator int() const = 0;
			inline virtual operator float() const = 0;
			inline virtual operator double() const = 0;
			inline virtual operator std::string() const = 0;
		public:
			inline virtual std::size_t Length() const = 0;
			inline virtual void Add(const Object& value_) = 0;
			inline virtual void Remove(const Object& value_) = 0;
			inline virtual void AddToFront(const Object& value_) = 0;
			inline virtual void RemoveFromFront(const Object& value_) = 0;
			inline virtual void AddToBack(const Object& value_) = 0;
			inline virtual void RemoveFromBack(const Object& value_) = 0;
			inline virtual void Insert(const std::size_t& index_, const Object& value_) = 0;
			inline virtual void Erase(const std::size_t& index_) = 0;
		};
#pragma region Proxy::Empty
		class Proxy::Empty:
			public Proxy
		{
		protected:
			inline Empty() = default;
			inline ~Empty() = default;
		public:
			inline Object operator [] (const Object& key_) const override
			{
				throw NotImplementedException();
			}
			inline Object& operator [] (const Object& key_) override
			{
				throw NotImplementedException();
			}
		public:
			inline operator std::nullptr_t() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline operator bool() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline operator int() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline operator float() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline operator double() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline operator std::string() const override
			{
				throw NotImplementedException(); // TODO
			}
		public:
			inline std::size_t Length() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline void Add(const Object& value_) override
			{
				throw NotImplementedException(); // TODO
			}
			inline void Remove(const Object& value_) override
			{
				throw NotImplementedException(); // TODO
			}
			inline void AddToFront(const Object& value_) override
			{
				throw NotImplementedException(); // TODO
			}
			inline void RemoveFromFront(const Object& value_) override
			{
				throw NotImplementedException(); // TODO
			}
			inline void AddToBack(const Object& value_) override
			{
				throw NotImplementedException(); // TODO
			}
			inline void RemoveFromBack(const Object& value_) override
			{
				throw NotImplementedException(); // TODO
			}
			inline void Insert(const std::size_t& index_, const Object& value_) override
			{
				throw NotImplementedException(); // TODO
			}
			inline void Erase(const std::size_t& index_) override
			{
				throw NotImplementedException(); // TODO
			}
		};
#pragma endregion
	protected:
		std::shared_ptr<Proxy> proxy;
	public:
		inline Object();
		inline Object(const Object&) = default;
		inline Object(Object&& source_);
		inline ~Object() = default;
	public:
		inline Object& operator = (const Object&) = default;
		inline Object& operator = (Object&& source_);
	protected:
		inline Object(const std::shared_ptr<Proxy>& proxy_):
			proxy(proxy_)
		{}
	public:
		inline Object(const std::nullptr_t&);
		inline Object(const bool& value_);
		inline Object(const int& value_);
		inline Object(const float& value_);
		inline Object(const double& value_);
		inline Object(const std::string& value_);
		inline Object(const char * const value_);
		inline Object(const std::initializer_list<Object>& value_);
		// TODO: implicit constructors
	public:
		inline Object operator [] (const Object& key_) const;
		inline Object& operator [] (const Object& key_);
	public:
		inline operator std::nullptr_t() const;
		inline operator bool() const;
		inline operator int() const;
		inline operator float() const;
		inline operator double() const;
		inline operator std::string() const;
		// TODO: cast operators
	public:
		template<class Derived> inline bool Is() const
		{
			auto derivedProxy = std::dynamic_pointer_cast<Derived::Proxy>(proxy);

			return derivedProxy != nullptr;
		}
	public:
		inline std::size_t Length() const;
		inline void Add(const Object& value_);
		inline void Remove(const Object& value_);
		inline void AddToFront(const Object& value_);
		inline void RemoveFromFront(const Object& value_);
		inline void AddToBack(const Object& value_);
		inline void RemoveFromBack(const Object& value_);
		inline void Insert(const std::size_t& index_, const Object& value_);
		inline void Erase(const std::size_t& index_);
	};
	class None:
		public Object
	{
		friend Object;
	protected:
		class Proxy:
			public Object::Proxy::Empty
		{
		public:
			inline operator std::nullptr_t() const override
			{
				return nullptr;
			}
		};
	public:
		inline None() = delete;
		inline None(const None&) = default;
		inline ~None() = default;
	public:
		inline None& operator = (const None&) = delete;
	};
	class Boolean:
		public Object
	{
		friend Object;
	protected:
		class Proxy:
			public Object::Proxy::Empty
		{
		protected:
			bool value;
		public:
			inline Proxy(const bool& value_):
				value(value_)
			{}
		public:
			inline virtual operator bool() const override
			{
				return value;
			}
		};
	public:
		inline Boolean() = delete;
		inline Boolean(const Boolean&) = delete;
		inline ~Boolean() = delete;
	public:
		inline Boolean& operator = (const Boolean&) = delete;
	};
	class Number:
		public Object
	{
		friend Object;
	protected:
		class Proxy:
			public Object::Proxy::Empty
		{
		};
		class Decimal;
	public:
		inline Number() = default;
		inline Number(const Number&) = delete;
		inline ~Number() = default;
	public:
		inline Number& operator = (const Number&) = delete;
	};
#pragma region Number::Decimal
	class Number::Decimal:
	public Number
	{
	protected:
		class Proxy:
			public Number::Proxy
		{
		};
	public:
		class Integer;
		class Float;
		class Double;
	public:
		inline Decimal() = default;
		inline ~Decimal() = default;
	};
#pragma endregion
#pragma region Number::Decimal::Integer
	class Number::Decimal::Integer:
	public Decimal
	{
	public:
		class Proxy:
			public Decimal::Proxy
		{
		protected:
			int value;
		public:
			inline Proxy(const int& value_):
				value(value_)
			{}
		public:
			inline virtual operator int() const
			{
				return value;
			}
			inline virtual operator float() const
			{
				return static_cast<float>(value);
			}
			inline virtual operator double() const
			{
				return static_cast<double>(value);
			}
		};
	};
#pragma endregion
#pragma region Number::Decimal::Float
	class Number::Decimal::Float:
	public Decimal
	{
	public:
		class Proxy:
			public Decimal::Proxy
		{
		protected:
			float value;
		public:
			inline Proxy(const float& value_):
				value(value_)
			{}
		public:
			inline Object operator [] (const Object& key_) const override
			{
				throw NotImplementedException();
			}
			inline Object& operator [] (const Object& key_) override
			{
				throw NotImplementedException();
			}
		public:
			inline virtual operator std::nullptr_t() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline virtual operator bool() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline virtual operator int() const
			{
				return static_cast<int>(value);
			}
			inline virtual operator float() const
			{
				return value;
			}
			inline virtual operator double() const
			{
				return static_cast<double>(value);
			}
			inline virtual operator std::string() const override
			{
				throw NotImplementedException(); // TODO
			}
		};
	};
#pragma endregion
#pragma region Number::Decimal::Double
	class Number::Decimal::Double:
	public Decimal
	{
	public:
		class Proxy:
			public Decimal::Proxy
		{
		protected:
			double value;
		public:
			inline Proxy(const double& value_):
				value(value_)
			{}
		public:
			inline Object operator [] (const Object& key_) const override
			{
				throw NotImplementedException();
			}
			inline Object& operator [] (const Object& key_) override
			{
				throw NotImplementedException();
			}
		public:
			inline virtual operator std::nullptr_t() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline virtual operator bool() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline virtual operator int() const
			{
				return static_cast<int>(value);
			}
			inline virtual operator float() const
			{
				return static_cast<float>(value);
			}
			inline virtual operator double() const
			{
				return value;
			}
			inline virtual operator std::string() const override
			{
				throw NotImplementedException(); // TODO
			}
		};
	};
#pragma endregion
	class String:
		public Object
	{
		friend Object;
	protected:
		class Proxy:
			public Object::Proxy::Empty
		{
		protected:
			std::string value;
		public:
			inline Proxy(const std::string& value_):
				value(value_)
			{}
		public:
			inline Object operator [] (const Object& key_) const override
			{
				if (!key_.Is<Number>())
				{
					throw NotImplementedException(); // TODO
				}

				auto index = static_cast<int>(key_);

				if (index < 0)
				{
					throw NotImplementedException(); // TODO
				}
				if (index >= static_cast<int>(value.size()))
				{
					throw NotImplementedException(); // TODO
				}

				return Object(std::to_string(value[index]));
			}
			/*inline Object& operator [] (const Object& key_) override
			{
				if (!key_.Is<Number>())
				{
					throw NotImplementedException(); // TODO
				}

				auto index = static_cast<int>(key_);

				if (index < 0)
				{
					throw NotImplementedException(); // TODO
				}
				if (index >= static_cast<int>(value.size()))
				{
					throw NotImplementedException(); // TODO
				}

				return Object(std::to_string(value[index])); // returning address of local variable
			}*/
		public:
			inline virtual operator std::string() const override
			{
				return value;
			}
		public:
			inline std::size_t Length() const override
			{
				return value.size();
			}
		};
	public:
		inline String() = delete;
		inline String(const String&) = delete;
		inline ~String() = delete;
	public:
		inline String& operator = (const String&) = delete;
	};
	class Array:
		public Object
	{
		friend Object;
	protected:
		class Proxy:
			public Object::Proxy::Empty
		{
		protected:
			std::vector<Object> objects;
		public:
			inline Proxy(const std::vector<Object>& objects_ = std::vector<Object>()):
				objects(objects_)
			{}
		private:
			std::vector<Object>::const_iterator ObtainIteratorFromIndex(const std::size_t& index_) const
			{
				auto it = objects.begin();

				for (std::size_t i = 0; i < index_; ++i)
				{
					++it;
				}

				return it;
			}
		public:
			inline Object operator [] (const Object& key_) const override
			{
				if (!key_.Is<Number>())
				{
					throw NotImplementedException(); // TODO
				}

				auto index = static_cast<int>(key_);

				if (index < 0)
				{
					throw NotImplementedException(); // TODO
				}
				if (index >= static_cast<int>(objects.size()))
				{
					throw NotImplementedException(); // TODO
				}

				return objects[index];
			}
			inline Object& operator [] (const Object& key_) override
			{
				if (!key_.Is<Number>())
				{
					throw NotImplementedException(); // TODO
				}

				auto index = static_cast<int>(key_);

				if (index < 0)
				{
					throw NotImplementedException(); // TODO
				}
				if (index >= static_cast<int>(objects.size()))
				{
					throw NotImplementedException(); // TODO
				}

				return objects[index];
			}
		public:
			inline std::size_t Length() const override
			{
				return objects.size();
			}
			inline void AddToFront(const Object& value_) override
			{
				objects.insert(objects.begin(), value_);
			}
			inline void RemoveFromFront(const Object& value_) override
			{
				objects.erase(objects.begin());
			}
			inline void AddToBack(const Object& value_) override
			{
				objects.push_back(value_);
			}
			inline void RemoveFromBack(const Object& value_) override
			{
				objects.pop_back();
			}
			inline void Add(const Object& value_) override
			{
				AddToBack(value_);
			}
			inline void Remove(const Object& value_) override
			{
				RemoveFromBack(value_);
			}
			inline void Insert(const std::size_t& index_, const Object& value_) override
			{
				objects.insert(ObtainIteratorFromIndex(index_), value_);
			}
			inline void Erase(const std::size_t& index_) override
			{
				objects.erase(ObtainIteratorFromIndex(index_));
			}
		};
	public:
		inline Array():
			Object(std::static_pointer_cast<Object::Proxy>(std::make_shared<Proxy>()))
		{
		}
		inline Array(const Array&) = delete;
		inline ~Array() = default;
	public:
		inline Array& operator = (const Array&) = delete;
	};

#pragma region Object
	Object::Object():
		proxy(std::make_shared<None::Proxy>())
	{}
	Object::Object(Object&& source_)
	{
		source_.proxy = nullptr;
	}

	Object& Object::operator = (Object&& source_)
	{
		proxy = source_.proxy;

		source_.proxy = nullptr;

		return *this;
	}

	Object::Object(const nullptr_t&):
		proxy(std::make_shared<None::Proxy>())
	{}
	Object::Object(const bool& value_) :
		proxy(std::make_shared<Boolean::Proxy>(value_))
	{
	}
	Object::Object(const int& value_) :
		proxy(std::make_shared<Number::Decimal::Integer::Proxy>(value_))
	{
	}
	Object::Object(const float& value_) :
		proxy(std::make_shared<Number::Decimal::Float::Proxy>(value_))
	{
	}
	Object::Object(const double& value_) :
		proxy(std::make_shared<Number::Decimal::Double::Proxy>(value_))
	{
	}
	Object::Object(const std::string& value_) :
		proxy(std::make_shared<String::Proxy>(value_))
	{
	}
	Object::Object(const char * const value_) :
		proxy(std::make_shared<String::Proxy>(value_))
	{
	}
	Object::Object(const std::initializer_list<Object>& value_) :
		proxy(std::make_shared<Array::Proxy>(value_))
	{
	}

	Object Object::operator [] (const Object& key_) const
	{
		return proxy->operator[](key_);
	}
	Object& Object::operator [] (const Object& key_)
	{
		return proxy->operator[](key_);
	}

	Object::operator std::nullptr_t() const
	{
		return proxy->operator std::nullptr_t();
	}
	Object::operator bool() const
	{
		return proxy->operator bool();
	}
	Object::operator int() const
	{
		return proxy->operator int();
	}
	Object::operator float() const
	{
		return proxy->operator float();
	}
	Object::operator double() const
	{
		return proxy->operator double();
	}
	Object::operator std::string() const
	{
		return proxy->operator std::string();
	}

	std::size_t Object::Length() const
	{
		return proxy->Length();
	}
	void Object::Add(const Object& value_)
	{
		proxy->Add(value_);
	}
	void Object::Remove(const Object& value_)
	{
		proxy->Remove(value_);
	}
	void Object::AddToFront(const Object& value_)
	{
		proxy->AddToFront(value_);
	}
	void Object::RemoveFromFront(const Object& value_)
	{
		proxy->RemoveFromFront(value_);
	}
	void Object::AddToBack(const Object& value_)
	{
		proxy->AddToBack(value_);
	}
	void Object::RemoveFromBack(const Object& value_)
	{
		proxy->RemoveFromBack(value_);
	}
	void Object::Insert(const std::size_t& index_, const Object& value_)
	{
		proxy->Insert(index_, value_);
	}
	void Object::Erase(const std::size_t& index_)
	{
		proxy->Erase(index_);
	}
#pragma endregion
}