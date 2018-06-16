#pragma once

#include <memory>
#include <string>


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
			inline Proxy() = default;
			inline Proxy(const Proxy&) = delete;
			inline virtual ~Proxy() = default;
		public:
			inline Proxy& operator = (const Proxy&) = delete;
		public:
			inline virtual operator std::nullptr_t() const = 0;
			inline virtual operator bool() const = 0;
			inline virtual operator int() const = 0;
			inline virtual operator float() const = 0;
			inline virtual operator double() const = 0;
		};
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
	public:
		inline Object(const std::nullptr_t&);
		inline Object(const bool& value_);
		inline Object(const int& value_);
		inline Object(const float& value_);
		inline Object(const double& value_);
		inline Object(const std::string& value_); // TODO
		// TODO: implicit constructors
	public:
		inline operator std::nullptr_t() const;
		inline operator bool() const;
		inline operator int() const;
		inline operator float() const;
		inline operator double() const;
		inline operator std::string() const; // TODO
		// TODO: cast operators
	};
	class None:
		public Object
	{
		friend Object;
	protected:
		class Proxy:
			public Object::Proxy
		{
		public:
			inline virtual operator std::nullptr_t() const override
			{
				return nullptr;
			}
			inline virtual operator bool() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline virtual operator int() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline virtual operator float() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline virtual operator double() const override
			{
				throw NotImplementedException(); // TODO
			}
		};
	public:
		inline None() = delete;
		inline None(const None&) = delete;
		inline ~None() = delete;
	public:
		inline None& operator = (const None&) = delete;
	};
	class Boolean:
		public Object
	{
		friend Object;
	protected:
		class Proxy:
			public Object::Proxy
		{
		protected:
			bool value;
		public:
			inline Proxy(const bool& value_):
				value(value_)
			{
			}
		public:
			inline virtual operator std::nullptr_t() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline virtual operator bool() const override
			{
				return value;
			}
			inline virtual operator int() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline virtual operator float() const override
			{
				throw NotImplementedException(); // TODO
			}
			inline virtual operator double() const override
			{
				throw NotImplementedException(); // TODO
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
		class Decimal
		{
		public:
			class Integer;
			class Float;
			class Double;
		};
	public:
		inline Number() = delete;
		inline Number(const Number&) = delete;
		inline ~Number() = delete;
	public:
		inline Number& operator = (const Number&) = delete;
	};
	class Number::Decimal::Integer
	{
	public:
		class Proxy:
			public Object::Proxy
		{
		protected:
			int value;
		public:
			inline Proxy(const int& value_):
				value(value_)
			{
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
	class Number::Decimal::Float
	{
	public:
		class Proxy:
			public Object::Proxy
		{
		protected:
			float value;
		public:
			inline Proxy(const float& value_):
				value(value_)
			{
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
		};
	};
	class Number::Decimal::Double
	{
	public:
		class Proxy:
			public Object::Proxy
		{
		protected:
			double value;
		public:
			inline Proxy(const double& value_):
				value(value_)
			{
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
		};
	};

#pragma region Object
	Object::Object():
		proxy(std::make_shared<None::Proxy>())
	{
	}
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
	{
	}
	Object::Object(const bool& value_):
		proxy(std::make_shared<Boolean::Proxy>(value_))
	{
	}
	Object::Object(const int& value_):
		proxy(std::make_shared<Number::Decimal::Integer::Proxy>(value_))
	{
	}
	Object::Object(const float& value_):
		proxy(std::make_shared<Number::Decimal::Float::Proxy>(value_))
	{
	}
	Object::Object(const double& value_):
		proxy(std::make_shared<Number::Decimal::Double::Proxy>(value_))
	{
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
#pragma endregion
}