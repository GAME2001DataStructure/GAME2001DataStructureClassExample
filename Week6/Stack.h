#pragma once

#include <cassert>

template<class T>
class Stack
{
public:
	// Constructor
	Stack(int size, int growBy = 1) : m_size(0), 
		m_top(-1), m_array(NULL), m_growSize(0)
	{
		if (size)
		{
			m_size = size;
			m_array = new T[m_size];	// Create a new array of size m_size

			assert(m_array != NULL);
			memset(m_array, 0, sizeof(T) * m_size);		// Explicitly allocating memory

			m_growSize = ((growBy > 0) ? growBy : 0);	// Force a 0 or positive growsize
		}
	}
	~Stack()
	{
		if (m_array != NULL)
		{
			delete[] m_array;
			m_array = NULL;
		}
	}
	// ---------------- STACK FUNCTIONS --------------------
	void push(T val)
	{
		assert(m_array != NULL);

		// Check to see if the stack is full. If true, expand its capacity
		if (isFull())
		{
			Expand();
		}

		m_array[++m_top] = val;	// Increment m_top THEN inserts val into the stack
	}
	void pop()
	{
		if (!isEmpty())
		{
			m_top--;
		}
	}
	const T& top() // Peeking at the top of the stack
	{
		assert(m_array != NULL);
		assert(m_top >= 0);	// Checking to see if m_top is pointing to an actual element in the stack

		return m_array[m_top];
	}
	// ---------------END STACK FUNCTIONS ------------------
	int GetSize()
	{
		return m_top + 1;	// Returns the number of items in my stack
	}
	int GetMaxSize()
	{
		return m_size;		// Returns the size of the stack
	}
	bool isEmpty()
	{
		return (m_top == -1);	// Is the stack empty?
	}
	bool isFull()
	{
		return (m_top == m_size - 1);	// Comparing the number of items in the stack to the size of the stack
	}
private:
	bool Expand()
	{
		// Is growsize a valid value to expand my stack
		if (m_growSize <= 0)
		{
			return false;	// Could not expand
		}
		assert(m_array != NULL);

		// Create a temporary (but larger) array
		T* temp = new T[m_size + m_growSize];
		assert(temp != NULL);

		// Copy the element from the original array to the new array
		memcpy(temp, m_array, sizeof(T) * m_size);

		delete[] m_array;	// Deletes the contents of the original array
		m_array = temp;		// Reassign the pointer from temp to m_array

		m_size += m_growSize;	// Update new size

		return true;
	}
private:
	// Variables
	T* m_array;		// Pointer to array
	int m_top;		// Represents the top of our stack
	int m_size;		// Size of the stack
	int m_growSize;	// How much can the stack grow by
};