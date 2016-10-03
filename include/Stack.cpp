#include "stack.hpp"

#ifndef STACK_CPP
#define STACK_CPP

template<typename T>
inline Stack<T>::Stack() : count_(0) {
}

template<typename T>
inline Stack<T>::Stack(Stack const & rhs) :	array_size_(rhs.array_size_),
						count_(rhs.count_) array_(copy(rsh.array_,rhs.count_,rhs.array_size_))  {
	
	
}

template<typename T>
inline Stack<T>::~Stack() {
	delete[] array_;
}

template<typename T>
inline auto Stack<T>::count() const -> size_t {
	return count_;
}

template<typename T>
inline auto Stack<T>::pop() -> T {
	if (count_ == 0) {
		throw std::logic_error("Stack is empty!");
	}
	return array_[--count_];
}



template<typename T>
inline auto Stack<T>::push(T const & value) -> void {
	 if (count_ == array_size_ ) {
	 	size_t size = array_size_ * 2 + (array_size_ == 0);
	 	 T * array = new T [size];
	 	 std::copy(array_, array_ + array_size_, array);
	 	 delete [] array_;
	 	 array_ = array;
	 	 array_size_ = size;
	 }
	 array_[count_ - 1] = value;
	 ++count_;
}
template<typename T>  
auto copy(const T * h, size_t sizeLeft, size_t sizeRight) -> T * {
	T * k_array = new T[sizeRight];
	try {
		std::copy(h, h + sizeLeft, k_array);
	}
	catch (...) {
		delete[] k_array;
		throw;
	}
	return k_array;
}
template<typename T>
inline auto Stack<T>::operator=(Stack const & rhs) -> Stack & {
	if (this != &rhs) {
		(Stack(rhs)).swap(*this);
	}
	return *this;
}

template<typename T>
auto Stack<T>::swap(Stack & rhs) -> void {
	std::swap(rhs.array_size_, array_size_);
	std::swap(rhs.array_, array_);
	std::swap(rhs.count_, count_);
}

template <typename T>
ostream & operator<<(ostream & output, Stack<T> const & stack) {
	for (size_t i = 0; i < stack.count_; ++i) {
		output << stack.array_[i] << " ";
	}
	output << std::endl;
	return output;
}
template<typename T>
bool stack<T>::operator==(stack const & h)
{
	if ((h.count_ != count_) || (h.array_size_ != array_size_)) {
		return false;
	}
	else {
		for (size_t i = 0; i < count_; i++) {
			if (h.array_[i] != array_[i]) {
				return false;
			}
		}
	}
	return true;
}


#endif 
