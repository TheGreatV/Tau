#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>


namespace Tau
{
	class None;
	class Boolean;
	class Number;

	enum class Type
	{
		None,
		Boolean,
		Number,
		String,
		Array,
		Map,
	};

	class Exception
	{
		// TODO
	};
	class NotImplementedException:
		public Exception
	{
		// TODO
	};

	class Object
	{
		friend Boolean;
		friend Number;
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
			inline virtual bool operator == (const std::shared_ptr<Proxy>& source_) const = 0;
		public:
			inline virtual operator std::nullptr_t() const = 0;
			inline virtual operator bool() const = 0;
			inline virtual operator int() const = 0;
			inline virtual operator float() const = 0;
			inline virtual operator double() const = 0;
			inline virtual operator std::string() const = 0;
		public:
			inline virtual Type Type() const = 0;
			inline virtual std::size_t Length() const = 0;
			inline virtual bool Has(const Object& value_) const = 0;
			inline virtual void Add(const Object& value_) = 0;
			inline virtual void Remove(const Object& value_) = 0;
			inline virtual void AddToFront(const Object& value_) = 0;
			inline virtual void RemoveFromFront(const Object& value_) = 0;
			inline virtual void AddToBack(const Object& value_) = 0;
			inline virtual void RemoveFromBack(const Object& value_) = 0;
			inline virtual void Insert(const std::size_t& index_, const Object& value_) = 0;
			inline virtual void Erase(const std::size_t& index_) = 0;
			inline virtual Object Keys() const = 0; // TODO: return Array?
			inline virtual Object Values() const = 0; // TODO: return Array?
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
			inline bool operator == (const std::shared_ptr<Proxy>& source_) const override
			{
				throw NotImplementedException(); // TODO
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
			inline virtual Tau::Type Type() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline std::size_t Length() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline bool Has(const Object& value_) const override
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
			inline Object Keys() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline Object Values() const override
			{
				throw NotImplementedException(); // TODO
			}
		};
#pragma endregion
		friend Proxy;
	public:
		class Comparator
		{
		public:
			inline bool operator () (const Object& left_, const Object& right_) const
			{
				return left_ != right_ && left_.proxy.get() < right_.proxy.get();
			}
		};
		friend Comparator;
		class Hash
		{
		public:
			inline std::size_t operator () (const Object& key_) const
			{
				return reinterpret_cast<std::size_t>(key_.proxy.get());
			}
		};
		friend Hash;
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
		{
		}
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
		inline Object operator [] (const char*const key_) const
		{
			return operator[](std::string(key_));
		}
		inline Object& operator [] (const char*const key_)
		{
			return operator[](std::string(key_));
		}
	public:
		inline bool operator == (const Object& source_) const
		{
			return proxy->operator == (source_.proxy);
		}
		inline bool operator != (const Object& source_) const
		{
			return !operator==(source_);
		}
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
		inline Type Type() const;
		inline std::size_t Length() const;
		inline bool Has(const Object& value_) const;
		inline void Add(const Object& value_);
		inline void Remove(const Object& value_);
		inline void AddToFront(const Object& value_);
		inline void RemoveFromFront(const Object& value_);
		inline void AddToBack(const Object& value_);
		inline void RemoveFromBack(const Object& value_);
		inline void Insert(const std::size_t& index_, const Object& value_);
		inline void Erase(const std::size_t& index_);
		inline Object Keys() const;
		inline Object Values() const;
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
			// inline bool operator == (const Object& source_) const override
			// {
			// 	return source_.Is<None>();
			// }
			inline bool operator == (const std::shared_ptr<Object::Proxy>& source_) const override
			{
				return std::dynamic_pointer_cast<Proxy>(source_) != nullptr;
			}
		public:
			inline Tau::Type Type() const override
			{
				return Type::None;
			}
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
			{
			}
		public:
			inline bool operator == (const std::shared_ptr<Object::Proxy>& source_) const override
			{
				return (std::dynamic_pointer_cast<Proxy>(source_) != nullptr) && (source_->operator bool() == value);
			}
		public:
			inline virtual operator bool() const override
			{
				return value;
			}
		public:
			inline Tau::Type Type() const override
			{
				return Type::Boolean;
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
	public:
		class Decimal;
	protected:
		class Proxy:
			public Object::Proxy::Empty
		{
		public:
			inline Tau::Type Type() const override
			{
				return Type::Number;
			}
		};
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
			inline bool operator == (const std::shared_ptr<Object::Proxy>& source_) const override;
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
			{
			}
		public:
			inline bool operator == (const std::shared_ptr<Object::Proxy>& source_) const override;
		public:
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
			inline bool operator == (const std::shared_ptr<Object::Proxy>& source_) const override;
		public:
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
		public:
			inline bool operator == (const std::shared_ptr<Object::Proxy>& source_) const override
			{
				return (std::dynamic_pointer_cast<Proxy>(source_) != nullptr) && (source_->operator std::string() == value);
			}
		public:
			inline virtual operator std::string() const override
			{
				return value;
			}
		public:
			inline Tau::Type Type() const override
			{
				return Type::String;
			}
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
				objects(std::move(objects_))
			{
			}
			inline ~Proxy() override = default;
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
			inline bool operator == (const std::shared_ptr<Object::Proxy>& source_) const override
			{
				// happy pass
				if (source_.get() == this)
				{
					return true;
				}
				
				if (std::dynamic_pointer_cast<Proxy>(source_) == nullptr)
				{
					return false;
				}
				
				const auto length = Length();
				
				if (source_->Length() != length)
				{
					return false;
				}
				
				for (int i = 0; i < static_cast<int>(length); ++i)
				{
					if (this->operator[](i) != source_->operator[](i))
					{
						return false;
					}
				}
				
				return true;
			}
		public:
			inline Tau::Type Type() const override
			{
				return Type::Array;
			}
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
			inline Object Values() const override
			{
				return Array(objects);
			}
		};
	public:
		inline Array():
			Object(std::static_pointer_cast<Object::Proxy>(std::make_shared<Proxy>()))
		{
		}
		inline Array(const std::vector<Object>& objects_):
			Object(std::static_pointer_cast<Object::Proxy>(std::make_shared<Proxy>(objects_)))
		{
		}
		inline Array(const Array&) = delete;
		inline ~Array() = default;
	public:
		inline Array& operator = (const Array&) = delete;
	};
	class Map:
		public Object
	{
		friend Object;
	public:
		using Pair = std::pair<Object, Object>;
		using Collection = std::unordered_map<Object, Object, Object::Hash>; // std::map<Object, Object, Object::Comparator>;
		using Initializer = std::vector<Pair>;
	protected:
		class Proxy:
			public Object::Proxy::Empty
		{
		protected:
			inline static Collection ObtainObjects(Initializer&& objects_)
			{
				Collection objects;

				for (auto &pair : objects_)
				{
					const auto it = objects.find(pair.first);

					if (it != objects.end())
					{
						throw NotImplementedException(); // TODO
					}

					objects.insert(pair);
				}

				return std::move(objects);
			}
		protected:
			Collection objects;
		public:
			inline Proxy(Initializer&& objects_ = Initializer()):
				objects(ObtainObjects(std::move(objects_)))
			{
			}
			inline ~Proxy() override = default;
		public:
			inline Object operator [] (const Object& key_) const override
			{
				const auto it = objects.find(key_);

				if (it == objects.end())
				{
					return nullptr;
				}

				const auto value = (*it).second;

				return value;
			}
			inline Object& operator [] (const Object& key_) override
			{
				return objects[key_];
			}
		public:
			inline bool operator == (const std::shared_ptr<Object::Proxy>& source_) const override
			{
				// happy pass
				if (source_.get() == this)
				{
					return true;
				}
				
				if (std::dynamic_pointer_cast<Proxy>(source_) == nullptr)
				{
					return false;
				}
				
				const auto keys = Keys();
				
				if (keys.Length() != source_->Keys().Length())
				{
					return false;
				}

				for (int i = 0; i < static_cast<int>(keys.Length()); ++i)
				{
					const auto &key = keys[i];

					if (!source_->Has(key))
					{
						return false;
					}
					if (this->operator [](key) != source_->operator[](key))
					{
						return false;
					}
				}
				
				return true;
			}
		public:
			inline Tau::Type Type() const override
			{
				return Type::Map;
			}
			inline std::size_t Length() const override
			{
				return objects.size();
			}
			inline bool Has(const Object& value_) const override
			{
				const auto it = objects.find(value_);

				return it != objects.end();
			}
			inline Object Keys() const override
			{
				std::vector<Object> values;

				values.reserve(objects.size());

				for (const auto &pair : objects)
				{
					values.push_back(pair.first);
				}

				return Array(std::move(values));
			}
			inline Object Values() const override
			{
				std::vector<Object> values;

				values.reserve(objects.size());

				for (const auto &pair : objects)
				{
					values.push_back(pair.second);
				}

				return Array(std::move(values));
			}
		};
	public:
		inline Map():
			Object(std::static_pointer_cast<Object::Proxy>(std::make_shared<Proxy>()))
		{
		}
		inline Map(Initializer&& objects_) :
			Object(std::static_pointer_cast<Object::Proxy>(std::make_shared<Proxy>(std::move(objects_))))
		{
		}
		inline Map(const Map&) = delete;
		inline ~Map() = default;
	public:
		inline Map& operator = (const Map&) = delete;
	};

#pragma region Object
	Object::Object():
		proxy(std::make_shared<None::Proxy>())
	{}
	Object::Object(Object&& source_):
		proxy(source_.proxy)
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

	Type Object::Type() const
	{
		return proxy->Type();
	}
	std::size_t Object::Length() const
	{
		return proxy->Length();
	}
	bool Object::Has(const Object& value_) const
	{
		return proxy->Has(value_);
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
	Object Object::Keys() const
	{
		return proxy->Keys();
	}
	Object Object::Values() const
	{
		return proxy->Values();
	}
#pragma endregion
#pragma region Array
	bool Number::Decimal::Integer::Proxy::operator == (const std::shared_ptr<Object::Proxy>& source_) const
	{
		return
			((std::dynamic_pointer_cast<Integer::Proxy>(source_) != nullptr) && (source_->operator int() == static_cast<int>(value))) ||
			((std::dynamic_pointer_cast<Float::Proxy>(source_) != nullptr) && (source_->operator float() == static_cast<float>(value))) ||
			((std::dynamic_pointer_cast<Double::Proxy>(source_) != nullptr) && (source_->operator double() == static_cast<double>(value)));
	}
	bool Number::Decimal::Float::Proxy::operator == (const std::shared_ptr<Object::Proxy>& source_) const
	{
		return
			((std::dynamic_pointer_cast<Integer::Proxy>(source_) != nullptr) && (source_->operator int() == static_cast<int>(value))) ||
			((std::dynamic_pointer_cast<Float::Proxy>(source_) != nullptr) && (source_->operator float() == static_cast<float>(value))) ||
			((std::dynamic_pointer_cast<Double::Proxy>(source_) != nullptr) && (source_->operator double() == static_cast<double>(value)));
	}
	bool Number::Decimal::Double::Proxy::operator == (const std::shared_ptr<Object::Proxy>& source_) const
	{
		return
			((std::dynamic_pointer_cast<Integer::Proxy>(source_) != nullptr) && (source_->operator int() == static_cast<int>(value))) ||
			((std::dynamic_pointer_cast<Float::Proxy>(source_) != nullptr) && (source_->operator float() == static_cast<float>(value))) ||
			((std::dynamic_pointer_cast<Double::Proxy>(source_) != nullptr) && (source_->operator double() == static_cast<double>(value)));
	}
#pragma endregion

	Map::Pair Pair(const Object& key_, const Object& value_)
	{
		return std::make_pair(key_, value_);
	}

	class Stringifier
	{
	protected:
		inline std::string Screen(const std::string& value_) const
		{
			const auto &withoutDoubleQuotes	= std::regex_replace(value_, std::regex("\""), "\\\"");
			const auto &withoutNewlines		= std::regex_replace(withoutDoubleQuotes, std::regex("\n"), "\\n");
			const auto &withoutNewlinesR	= std::regex_replace(withoutNewlines, std::regex("\r"), "\\r");
			const auto &withoutTabulation	= std::regex_replace(withoutNewlinesR, std::regex("\t"), "\\t");

			return std::move(withoutTabulation);
		}
		inline std::string Tab(const std::size_t level_) const
		{
			std::string result;

			for (std::size_t i = 0; i < level_; ++i)
			{
				result += "\t";
			}

			return result;
		}
		inline std::string Stringify(const Object& object_, const std::size_t level_) const
		{
			// TODO: visitor
			if (object_.Type() == Type::None)
			{
				return "none";
			}
			else if (object_.Type() == Type::Boolean)
			{
				const auto &value = static_cast<bool>(object_);

				return value
					? "true"
					: "false";
			}
			else if (object_.Is<Number::Decimal::Integer>())
			{
				const auto &value = static_cast<int>(object_);

				return std::to_string(value);
			}
			else if (object_.Is<Number::Decimal::Float>())
			{
				const auto &value = static_cast<float>(object_);

				return std::to_string(value);
			}
			else if (object_.Is<Number::Decimal::Double>())
			{
				const auto &value = static_cast<double>(object_);

				return std::to_string(value);
			}
			else if (object_.Is<String>())
			{
				const auto &value		= static_cast<std::string>(object_);
				const auto &screened	= Screen(value);

				return "\"" + screened + "\"";
			}
			else if (object_.Is<Array>())
			{
				const auto values		= object_.Values();
				const auto nextLevel	= level_ + 1;

				std::string stringifiedValues = "";

				for (int i = 0; i < static_cast<int>(values.Length()); ++i)
				{
					const auto value			= values[i];
					const auto stringifiedValue	= Stringify(value, nextLevel);

					stringifiedValues += Tab(nextLevel) + stringifiedValue + ",\n";
				}

				return "[\n" + stringifiedValues + Tab(level_) + "]";
			}
			else if (object_.Is<Map>())
			{
				const auto keys = object_.Keys();
				const auto nextLevel = level_ + 1;

				std::string stringifiedValues = "";

				for (int i = 0; i < static_cast<int>(keys.Length()); ++i)
				{
					const auto key = keys[i];
					const auto value = object_[key];
					const auto stringifiedKey = Stringify(key, nextLevel);
					const auto stringifiedValue = Stringify(value, nextLevel);

					stringifiedValues += Tab(nextLevel) + stringifiedKey + ": " + stringifiedValue + ",\n";
				}

				return "{\n" + stringifiedValues + Tab(level_) + "}";
			}

			throw NotImplementedException();
		}
	public:
		inline std::string Stringify(const Object& object_) const
		{
			return Stringify(object_, 0);
		}
	};
}


#pragma region
#pragma endregion
