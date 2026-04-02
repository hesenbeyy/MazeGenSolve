#ifndef STACK_HPP
#define STACK_HPP
#include <string>
#include "macros.hpp"

class StackException {
public:
	std::string error;
	StackException(const std::string& err) : error(err) {}
};

template <typename T>
class Stack {
private: 
	std::vector<T> stack;
	int top;

public:
	Stack() : top(-1) { stack.resize(MAX_SIZE); }
	bool isEmpty();
	bool isFull();
	void push(const T& val);
	void pop();
	T peek();
};

template <typename T>
bool Stack<T>::isFull() {
	return top + 1 >= MAX_SIZE;
}

template <typename T>
bool Stack<T>::isEmpty() {
	return top == -1;
}

template <typename T>
void Stack<T>::pop() {
	if (isEmpty()) {
		throw StackException("Stack underflow");
	}

	top--;
}

template <typename T>
void Stack<T>::push(const T& val) {
	if (isFull()) {
		throw StackException("Stack overflow");
	}

	stack[++top] = val;
}

template <typename T>
T Stack<T>::peek() {
	if (isEmpty()) {
		throw StackException("Stack is empty");
	}
	return stack[top];
}

#endif