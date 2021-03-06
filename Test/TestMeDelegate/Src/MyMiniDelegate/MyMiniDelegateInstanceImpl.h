#ifndef __MyMiniDelegateInstanceImpl_H
#define __MyMiniDelegateInstanceImpl_H

#include "MyMiniDelegateInstanceBase.h"

namespace MyNS
{
// we have C++11 support...yeah!
/**
 * non specialized template declaration for delegate
 */
template <typename T>
class MyMiniDelegateInstanceImpl;

/**
 * specialization for member functions
 *
 * \tparam T            class-type of the object who's member function to call
 * \tparam R            return type of the function that gets captured
 * \tparam params       variadic template list for possible arguments
 *                      of the captured function
 */
template <typename T, typename R, typename... ParamTypes>
class MyMiniDelegateInstanceImpl<R (T::*)(ParamTypes...)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*func_type)(ParamTypes...);

	MyMiniDelegateInstanceImpl(func_type func, T& callee)
        : callee_(callee)
        , func_(func)
    {}

    R operator()(ParamTypes... args) const
    {
        return (callee_.*func_)(args...);
    }

    bool operator==(const MyMiniDelegateInstanceImpl& other) const
    {
        return (&callee_ == &other.callee_) && (func_ == other.func_);
    }
    bool operator!= (const MyMiniDelegateInstanceImpl& other) const
    {
        return !((*this) == other);
    }

private:
    T& callee_;
    func_type func_;
};

/**
 * specialization for const member functions
 */
template <typename T, typename R, typename... ParamTypes>
class MyMiniDelegateInstanceImpl<R (T::*)(ParamTypes...) const> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*func_type)(ParamTypes...) const;

	MyMiniDelegateInstanceImpl(func_type func, const T& callee)
        : callee_(callee)
        , func_(func)
    {}

    R operator()(ParamTypes... args) const
    {
        return (callee_.*func_)(args...);
    }

    bool operator==(const MyMiniDelegateInstanceImpl& other) const
    {
        return (&callee_ == &other.callee_) && (func_ == other.func_);
    }
    bool operator!= (const MyMiniDelegateInstanceImpl& other) const
    {
        return !(*this == other);
    }

private:
    const T& callee_;
    func_type func_;
};

/**
 * specialization for free functions
 *
 * \tparam R            return type of the function that gets captured
 * \tparam params       variadic template list for possible arguments
 *                      of the captured function
 */
template <typename R, typename... ParamTypes>
class MyMiniDelegateInstanceImpl<R (*)(ParamTypes...)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (*func_type)(ParamTypes...);

	MyMiniDelegateInstanceImpl(func_type func)
        : func_(func)
    {}

    R operator()(ParamTypes... args) const
    {
        return (*func_)(args...);
    }

    bool operator==(const MyMiniDelegateInstanceImpl& other) const
    {
        return func_ == other.func_;
    }
    bool operator!= (const MyMiniDelegateInstanceImpl& other) const
    {
        return !((*this) == other);
    }

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
    func_type func_;
};

/**
 * function to deduce template parameters from call-context
 */
template <typename F, typename T>
MyMiniDelegateInstanceImpl<F>* make_delegate(F func, T& obj)
{
    return new MyMiniDelegateInstanceImpl<F>(func, obj);
}

template <typename T>
MyMiniDelegateInstanceImpl<T>* make_delegate(T func)
{
    return new MyMiniDelegateInstanceImpl<T>(func);
}

} // namespace delegate

#endif /* end of include guard */
