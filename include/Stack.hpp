#pragma once
#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
template<typename T>
auto copy(const T * rhs, size_t sizeLeft, size_t sizeRight)->T *; /*strong*/
template <typename T1, typename T2>
auto construct(T1 * ptr, T2 const & value) -> void;
template <typename T>
auto destroy(T * ptr) noexcept -> void;
template <typename FwdIter>
auto destroy(FwdIter first, FwdIter last) noexcept -> void;
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



