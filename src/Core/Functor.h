#pragma once

#include "StringUtils.h"
#include "Exceptions.h"
#include <string>

namespace CasaEngine
{
	class IFunction
	{
	public:
		virtual ~IFunction() = default;
		virtual std::string Execute(const std::string& Params) = 0;
	};

	class Functor
	{
	public:
		Functor(IFunction* Func = nullptr);
		std::string operator ()(const std::string& Params = "") const;

	private:
		IFunction* m_pFunction;
	};

	inline Functor::Functor(IFunction* Func) :
		m_pFunction(Func)
	{
	}

	inline std::string Functor::operator ()(const std::string& Params) const
	{
		if (!m_pFunction)
		{
			throw Exception("Try o call a null function through a functor");
		}

		return m_pFunction->Execute(Params);
	}

	template <typename T> struct Base { typedef T Type; };
	template <typename T> struct Base<T&> { typedef T Type; };
	template <typename T> struct Base<const T> { typedef T Type; };
	template <typename T> struct Base<const T&> { typedef T Type; };

	template <typename Ret>
	struct CallFun
	{
		template <typename FuncType>
		static std::string Do(FuncType Func)
		{
			return CStringBuilder(Func());
		}

		template <typename FuncType, typename Arg1>
		static std::string Do(FuncType Func, Arg1 a1)
		{
			return CStringBuilder(Func(a1));
		}

		template <typename FuncType, typename Arg1, typename Arg2>
		static std::string Do(FuncType Func, Arg1 a1, Arg2 a2)
		{
			return CStringBuilder(Func(a1, a2));
		}
	};

	template <>
	struct CallFun<void>
	{
		template <typename FuncType>
		static std::string Do(FuncType Func)
		{
			Func();
			return "";
		}

		template <typename FuncType, typename Arg1>
		static std::string Do(FuncType Func, Arg1 a1)
		{
			Func(a1);
			return "";
		}

		template <typename FuncType, typename Arg1, typename Arg2>
		static std::string Do(FuncType Func, Arg1 a1, Arg2 a2)
		{
			Func(a1, a2);
			return "";
		}
	};

	template <typename Ret, typename ParamType>
	struct CallMemFun
	{
		template <typename FuncType>
		static std::string Do(ParamType Obj, FuncType Func)
		{
			return CStringBuilder((Obj.*Func)());
		}

		template <typename FuncType, typename Arg1>
		static std::string Do(ParamType Obj, FuncType Func, Arg1 a1)
		{
			return CStringBuilder((Obj.*Func)(a1));
		}

		template <typename FuncType, typename Arg1, typename Arg2>
		static std::string Do(ParamType Obj, FuncType Func, Arg1 a1, Arg2 a2)
		{
			return CStringBuilder((Obj.*Func)(a1, a2));
		}
	};

	template <typename ParamType>
	struct CallMemFun<void, ParamType>
	{
		template <typename FuncType>
		static std::string Do(ParamType Obj, FuncType Func)
		{
			(Obj.*Func)();
			return "";
		}

		template <typename FuncType, typename Arg1>
		static std::string Do(ParamType Obj, FuncType Func, Arg1 a1)
		{
			(Obj.*Func)(a1);
			return "";
		}

		template <typename FuncType, typename Arg1, typename Arg2>
		static std::string Do(ParamType Obj, FuncType Func, Arg1 a1, Arg2 a2)
		{
			(Obj.*Func)(a1, a2);
			return "";
		}
	};

	template <typename Ret>
	class CFunction0 : public IFunction
	{
		virtual std::string Execute(const std::string& Params)
		{
			CStringExtractor(Params.c_str()).ThrowIfEOF();

			return CallFun<Ret>::Do(m_Func);
		}

		typedef Ret(*TFuncType)();
		TFuncType m_Func;

	public:

		CFunction0(TFuncType Func) : m_Func(Func) {}
	};

	template <typename Ret, typename Arg1>
	class CFunction1 : public IFunction
	{
	private:

		virtual std::string Execute(const std::string& Params)
		{
			typename Base<Arg1>::Type a1;
			CStringExtractor(Params.c_str())(a1).ThrowIfEOF();

			return CallFun<Ret>::Do(m_Func, a1);
		}

		typedef Ret(*TFuncType)(Arg1);
		TFuncType m_Func;

	public:

		CFunction1(TFuncType Func) : m_Func(Func) {}
	};

	template <typename Ret, typename Arg1, typename Arg2>
	class CFunction2 : public IFunction
	{
	private:

		virtual std::string Execute(const std::string& Params)
		{
			typename Base<Arg1>::Type a1;
			typename Base<Arg2>::Type a2;
			CStringExtractor(Params.c_str())(a1)(a2).ThrowIfEOF();

			return CallFun<Ret>::Do(m_Func, a1, a2);
		}

		typedef Ret(*TFuncType)(Arg1, Arg2);
		TFuncType m_Func;

	public:

		CFunction2(TFuncType Func) : m_Func(Func) {}
	};

	template <typename ParamType, typename FuncType, typename Ret>
	class CFunctionMem0 : public IFunction
	{
	private:

		virtual std::string Execute(const std::string& Params)
		{
			try { CStringExtractor(Params.c_str()).ThrowIfEOF(); }
			catch (BadConversion& e) { return "The argument is empty"; }

			return CallMemFun<Ret, ParamType>::Do(m_Obj, m_Func);
		}

		FuncType  m_Func;
		ParamType m_Obj;

	public:

		CFunctionMem0(FuncType Func, ParamType Obj) :
			m_Func(Func), m_Obj(Obj)
		{
		}

		CFunctionMem0& operator=(const CFunctionMem0& rsh_)
		{
			m_Func = rsh_.m_Func;
			m_Obj = rsh_.m_Obj;
		}
	};

	template <typename ParamType, typename FuncType, typename Ret, typename Arg1>
	class CFunctionMem1 : public IFunction
	{
	private:

		virtual std::string Execute(const std::string& Params)
		{
			typename Base<Arg1>::Type a1;

			try { CStringExtractor(Params.c_str())(a1).ThrowIfEOF(); }
			catch (BadConversion& e) { return "The command needs 1 arguments"; }

			return CallMemFun<Ret, ParamType>::Do(m_Obj, m_Func, a1);
		}

		FuncType  m_Func;
		ParamType m_Obj;

	public:

		CFunctionMem1(FuncType Func, ParamType Obj) : m_Func(Func), m_Obj(Obj) {}
	};

	template <typename ParamType, typename FuncType, typename Ret, typename Arg1, typename Arg2>
	class CFunctionMem2 : public IFunction
	{
	private:

		virtual std::string Execute(const std::string& Params)
		{
			typename Base<Arg1>::Type a1;
			typename Base<Arg2>::Type a2;

			try { CStringExtractor(Params.c_str())(a1)(a2).ThrowIfEOF(); }
			catch (BadConversion&/*e*/) { return "The command needs 2 arguments"; }

			return CallMemFun<Ret, ParamType>::Do(m_Obj, m_Func, a1, a2);
		}

		FuncType  m_Func;
		ParamType m_Obj;

	public:

		CFunctionMem2(FuncType Func, ParamType Obj) : m_Func(Func), m_Obj(Obj) {}
	};

	template <typename Class, typename Ret>
	inline Functor BindCopy(Ret(Class::* Func)(), Class Obj)
	{
		return new CFunctionMem0<Class, Ret(Class::*)(), Ret>(Func, Obj);
	}

	template <typename Class, typename Ret, typename Arg1>
	inline Functor BindCopy(Ret(Class::* Func)(Arg1), Class Obj)
	{
		return new CFunctionMem1<Class, Ret(Class::*)(Arg1), Ret, Arg1>(Func, Obj);
	}

	template <typename Class, typename Ret, typename Arg1, typename Arg2>
	inline Functor BindCopy(Ret(Class::* Func)(Arg1, Arg2), Class Obj)
	{
		return new CFunctionMem2<Class, Ret(Class::*)(Arg1, Arg2), Ret, Arg1, Arg2>(Func, Obj);
	}

	template <typename Class, typename Ret>
	inline Functor BindCopy(Ret(Class::* Func)() const, Class Obj)
	{
		return new CFunctionMem0<Class, Ret(Class::*)() const, Ret>(Func, Obj);
	}

	template <typename Class, typename Ret, typename Arg1>
	inline Functor BindCopy(Ret(Class::* Func)(Arg1) const, Class Obj)
	{
		return new CFunctionMem1<Class, Ret(Class::*)(Arg1) const, Ret, Arg1>(Func, Obj);
	}

	template <typename Class, typename Ret, typename Arg1, typename Arg2>
	inline Functor BindCopy(Ret(Class::* Func)(Arg1, Arg2) const, Class Obj)
	{
		return new CFunctionMem2<Class, Ret(Class::*)(Arg1, Arg2) const, Ret, Arg1, Arg2>(Func, Obj);
	}

	template <typename T>
	inline Functor Bind(T Obj)
	{
		return BindCopy(&T::operator (), Obj);
	}

	template <typename Ret>
	inline Functor Bind(Ret(*Func)())
	{
		return new CFunction0<Ret>(Func);
	}

	template <typename Ret, typename Arg1>
	inline Functor Bind(Ret(*Func)(Arg1))
	{
		return new CFunction1<Ret, Arg1>(Func);
	}

	template <typename Ret, typename Arg1, typename Arg2>
	inline Functor Bind(Ret(*Func)(Arg1, Arg2))
	{
		return new CFunction2<Ret, Arg1, Arg2>(Func);
	}

	template <typename Class, typename ParamType, typename Ret>
	inline Functor Bind(Ret(Class::* Func)(), ParamType& Obj)
	{
		return new CFunctionMem0<ParamType&, Ret(Class::*)(), Ret>(Func, Obj);
	}

	template <typename Class, typename ParamType, typename Ret, typename Arg1>
	inline Functor Bind(Ret(Class::* Func)(Arg1), ParamType& Obj)
	{
		return new CFunctionMem1<ParamType&, Ret(Class::*)(Arg1), Ret, Arg1>(Func, Obj);
	}

	template <typename Class, typename ParamType, typename Ret, typename Arg1, typename Arg2>
	inline Functor Bind(Ret(Class::* Func)(Arg1, Arg2), ParamType& Obj)
	{
		return new CFunctionMem2<ParamType&, Ret(Class::*)(Arg1, Arg2), Ret, Arg1, Arg2>(Func, Obj);
	}

	template <typename Class, typename ParamType, typename Ret>
	inline Functor Bind(Ret(Class::* Func)() const, const ParamType& Obj)
	{
		return new CFunctionMem0<const ParamType&, Ret(Class::*)() const, Ret>(Func, Obj);
	}

	template <typename Class, typename ParamType, typename Ret, typename Arg1>
	inline Functor Bind(Ret(Class::* Func)(Arg1) const, const ParamType& Obj)
	{
		return new CFunctionMem1<const ParamType&, Ret(Class::*)(Arg1) const, Ret, Arg1>(Func, Obj);
	}

	template <typename Class, typename ParamType, typename Ret, typename Arg1, typename Arg2>
	inline Functor Bind(Ret(Class::* Func)(Arg1, Arg2) const, const ParamType& Obj)
	{
		return new CFunctionMem2<const ParamType&, Ret(Class::*)(Arg1, Arg2) const, Ret, Arg1, Arg2>(Func, Obj);
	}

}

