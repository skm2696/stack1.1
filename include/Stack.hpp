#include <cstdlib>
#include <iostream>
#include <memory>
//#include <cassert>
#ifndef STACK_HPP
#define STACK_HPP

using std::size_t;
using std::ostream;

template<typename T>
class Stack;

template<typename T>
ostream & operator<<(ostream & output, Stack<T> & stack);

template<typename T>
class Stack {
public:
    Stack();    /*noexcept*/
    Stack(Stack const & rhs);   /*strong*/
    ~Stack();   /*noexcept*/
    auto count() const -> size_t;   /*noexcept*/
    auto pop() -> T;    /*basic*/
    auto push(T const & value) -> void;    /*strong*/
    bool operator==(stack const & h);   /*noexcept*/
    auto operator=(Stack const & rhs) -> Stack &;   /*strong*/
private:
   
    size_t array_size_;
    size_t count_;
     T * array_;
    auto swap(Stack & rhs) -> void;
};

#include "stack.cpp"

#endif // STACK_HPP

