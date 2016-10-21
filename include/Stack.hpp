#pragma once
#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
template <typename T1, typename T2>
void construct(T1 * ptr, T2 const & value);
template <typename T>
void destroy(T * ptr) noexcept;
template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept;
template<typename T>
class allocator
{
protected:
	allocator(size_t size = 0);
	~allocator();
	void swap(allocator& stk);
	allocator(allocator const&) = delete;
	allocator& operator=(allocator const&) = delete;

	T * array_;
	size_t array_size_;
	size_t count_;
};
template <typename T>
class stack : private allocator<T>
{
public:
	stack();
	~stack();
	stack(const stack & obj);
	size_t count() const noexcept;
	void push(T const &);
	size_t pop();
	const T& top();
	stack & operator=(const stack &obj);
	bool operator==(stack const & rhs);
	
};
#include "Stack.cpp"
#endif



