#pragma once

#include <cassert>
#include "DoublyLinkList.h"

template<class T>
class Stack
{
public:
	// Constructor
	Stack() {}
	~Stack() {}
	// --------------- STACK FUNCTIONS ------------------------
	void push(T val)
	{
		m_container.Push(val);
	}
	void pop()
	{
		m_container.Pop();
	}
	const T& top()
	{
		LinkIterator<T> it;
		it = m_container.Last();	// Sets the iterator to the last node
		return *it;
	}
	// --------------END STACK FUNCTIONS-----------------------
	int GetSize()
	{
		return m_container.GetSize();
	}
	bool isEmpty()
	{
		return (m_container.GetSize() == 0);
	}
private:
	// Variables
	LinkList<T> m_container;
	// int m_size;  // BOOK ERROR! NEVER USED
};