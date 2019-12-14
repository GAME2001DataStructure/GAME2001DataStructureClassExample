#pragma once
// Queue -- Getting in for a purchase (FIFO)

#include "DoublyLinkList.h"

template<class T>
class PriorityQueue
{
public:
	// Constructor & Destructor
	PriorityQueue(int size)
	{
		assert(size > 0);
		m_size = size;
	}
	~PriorityQueue() { }
	// Queue Functions
	void push(T val)
	{
		if (m_elements.GetSize() < m_size)
		{
			m_elements.Push(val);
		}
	}
	void pop()
	{
		m_elements.Pop_Front();
	}
	T& front() // Return a reference to the front of my queue
	{
		LinkIterator<T> it;
		it = m_elements.Begin();	// Points to the beginning of my link list

		return *it;					// Returns the derefences iterator (or the value of the node)
	}
	T& back()
	{
		LinkIterator<T> it;
		it = m_elements.Last();		// Points to the last node of the link list

		return *it;
	}
	// Helper Functions
	int GetSize()
	{
		return m_elements.GetSize();
	}
	int GetMaxSize()
	{
		return m_size;
	}
	bool isEmpty()
	{
		return (m_elements.GetSize() == 0);
	}
	void Resize(int size)
	{
		assert(size > 0);
		m_size = size;
	}
private:
	LinkList<T> m_elements;		// Link List structure
	int m_size;					// Size of our queue
};