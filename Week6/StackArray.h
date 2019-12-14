#pragma once

#include <cassert>
#include "UnorderedArray.h"

template<class T>
class Stack
{
public:
	// Constructor
	Stack(int size, int growBy = 1)
	{
		assert(size > 0 && growBy >= 0);	// Input validation
		m_container = new UnorderedArray<T>(size, growBy);	// Initialize unorderedarray
		assert(m_container != NULL);
	}
	~Stack()
	{
		if (m_container != NULL)
		{
			delete m_container;
			m_container = NULL;
		}
	}
	// ----------------- STACK FUNCTIONS ------------------------
	void push(T val)
	{
		assert(m_container != NULL);
		m_container->push(val);
	}
	void pop()
	{
		assert(m_container != NULL);
		m_container->pop();
	}
	const T& top()
	{
		assert(m_container != NULL);
		// Dereferencing our pointer to the array. Then using array notation to return the top element
		return (*m_container)[m_container->GetSize() - 1];
	}
	// ----------------END STACK FUNCTIONS-----------------------
	int GetSize()
	{
		assert(m_container != NULL);
		return m_container->GetSize();
	}
	int GetMaxSize()
	{
		assert(m_container != NULL);
		return m_container->GetMaxSize();
	}
	bool isEmpty()
	{
		assert(m_container != NULL);
		return (m_container->GetSize() == 0);	// Check to see if my stack has 0 items
	}
private:
	// Variables
	UnorderedArray<T>* m_container;
};