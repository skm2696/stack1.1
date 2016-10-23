#include "Stack.hpp"
#include <stdexcept>
#ifndef STACK_CPP
#define STACK_CPP
template <typename T1, typename T2>
void construct(T1 * ptr, T2 const & value)
{
	new(ptr) T1(value);
}

template <typename T>
void destroy(T * array) noexcept
{
	array->~T();
}

template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept
{
	for (; first != last; ++first) 
	{
		destroy(&*first);
	}
}



template <typename T>
T* copy_n(const T * arr, size_t count, size_t array_size)
{
	T * vit = new T[array_size];
	try
	{
		std::copy(arr, arr + count, vit);
	}
	catch (...)
	{
		delete[] vit;
		throw;
	}
	return vit;
};
template <typename T>
allocator<T>::allocator(size_t size) : array_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))), array_size_(size), count_(0) {
};
template <typename T>
allocator<T>::~allocator() 
{
	operator delete(array_);
};
template <typename T>
void allocator<T>::swap(allocator& stk)
{
	std::swap(array_, stk.array_);
	std::swap(array_size_, stk.array_size_);
	std::swap(count_, stk.count_);
};

template <typename T>
stack<T>::stack(size_t size)  : allocator<T>(size)
{}
template <typename T>
size_t stack<T>::count() const noexcept
{
	return allocator<T>::count_;
}
template <typename T>
void stack<T>::push(T const &v)
{

	if (allocator<T>::count_ == allocator<T>::array_size_)
	{
		size_t array_size = allocator<T>::array_size_*2+(allocator<T>::array_size_==0);
		stack<T> temp(array_size);
		while (temp.count() < allocator<T>::count_) temp.push(allocator<T>::array_[temp.count()]); 
		this->swap(temp);
	}
	construct(allocator<T>::array_ + allocator<T>::count_, v);
	++allocator<T>::count_;

}
template <typename T>
size_t stack<T>::pop()
{
	if (allocator<T>::count_ == 0)
	{
		throw std::logic_error("Stack is empty!");
	}
	destroy(allocator<T>::array_ + allocator<T>::count_);
	--allocator<T>::count_;
}
template <typename T>
const T& stack<T>::top()
{
	if (allocator<T>::count_ == 0)
	{
		throw std::logic_error("Stack is empty!");
	}
	return allocator<T>::array_[allocator<T>::count_ - 1];
}
template <typename T>
stack<T>::~stack()
{
	destroy(allocator<T>::array_, allocator<T>::array_ + allocator<T>::count_);
}

template <typename T>
stack<T>::stack(const stack&tmp) 
{
	allocator<T>::count_ = tmp.count_;
	allocator<T>::array_size_ = tmp.array_size_;
	allocator<T>::array_=copy_n(tmp.array_, tmp.count_, tmp.array_size_); 
}
template <typename T>
stack<T>& stack<T>::operator=(const stack &obj)
{

	if (this != &obj)
	{
		T* vit = copy_n(obj.array_, obj.count_, obj.array_size_);
		delete[] allocator<T>::array_;
		allocator<T>::array_ = vit;
		allocator<T>::array_size_ = obj.array_size_;
		allocator<T>::count_ = obj.count_;
	}

	return *this;
}

template<typename T>
bool stack<T>::operator==(stack const & vit)
{
	if ((vit.count_ != allocator<T>::count_) || (vit.array_size_ != allocator<T>::array_size_)) {
		return false;
	}
	else {
		for (size_t i = 0; i < allocator<T>::count_; i++) {
			if (vit.array_[i] != allocator<T>::array_[i]) {
				return false;
			}
		}
	}
	return true;
}
template<typename T> 
bool stack<T>::empty() const noexcept
{
	return (allocator<T>::count_ == 0);
}
#endif
