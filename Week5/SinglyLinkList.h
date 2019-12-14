#pragma once
#include <cassert>

template<class T> class LinkIterator;
template<class T> class LinkList;

// Describes a single node
template <class T>
class LinkNode
{
	// Giving access to the private member variables
	friend class LinkIterator<T>;
	friend class LinkList<T>;

private:
	T m_data;
	LinkNode* m_next;
};

// Be used to access, manipulate and traverse our link list
template <class T>
class LinkIterator
{
public:
	LinkIterator()
	{
		m_node = NULL;
	}
	~LinkIterator()
	{
	}
	// -------------- OVERLOADED OPERATORS ------------------
	// Assignment operator (=)
	void operator=(LinkNode<T>* node)
	{
		m_node = node;
	}
	// Dereferencing operator (*)
	T& operator*()
	{
		assert(m_node != NULL);
		return m_node->m_data;
	}
	// Incremental operators (++) -- Prefix and Postfix
	void operator++()	// Prefix
	{
		assert(m_node != NULL);
		m_node = m_node->m_next;
	}
	void operator++(int) // Postfix
	{
		assert(m_node != NULL);
		m_node = m_node->m_next;
	}
	// Comparison operators (!= & ==)
	bool operator!=(LinkNode<T>* node)
	{
		return (m_node != node);
	}
	bool operator==(LinkNode<T>* node)
	{
		return (m_node == node);
	}
	// ------------ END OVERLOADED OPERATORS ----------------
private:
	LinkNode<T>* m_node;	// Points to a node in the link list
};

// Actual link list structure
template <class T>
class LinkList
{
public:
	LinkList() : m_size(0), m_root(0), m_lastNode(0)
	{
	}
	~LinkList()
	{
		while (m_root)
		{
			Pop();
		}
	}
	// ---------------- POSITIONING FUNCTIONS ---------------------
	LinkNode<T>* Begin()
	{
		assert(m_root != NULL);
		return m_root;
	}
	LinkNode<T>* End()
	{
		return NULL;
	}
	LinkNode<T>* Last()
	{
		return m_lastNode;
	}
	// -------------- END POSITIONING FUNCTIONS -------------------
	// -------------- LINK LIST OPERATIONS ------------------------
	void Push(T newData)
	{
		// Create a standalone LinkNode object
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != NULL);
		node->m_data = newData;
		node->m_next = NULL;

		// Add new LinkNode to the existing link list
		if (m_lastNode != NULL) // Items currently exist in the link list
		{
			m_lastNode->m_next = node;
			m_lastNode = node;
		}
		else // An empty link list
		{
			m_root = node;
			m_lastNode = node;
		}

		m_size++;
	}
	void Pop()
	{
		assert(m_root != NULL);

		if (m_root->m_next == NULL) // Check is only 1 node is in the link list
		{
			delete m_root;
			m_root = NULL;
			m_lastNode = NULL;
		}
		else // Link list has 2 or more items in the list
		{
			LinkNode<T>* prevNode = m_root;

			// Traverse the link list until we reach the end
			while (prevNode->m_next != NULL && prevNode->m_next != m_lastNode)
			{
				prevNode = prevNode->m_next;
			}

			// PrevNode now at the 2nd last node in the link list
			delete m_lastNode;
			prevNode->m_next = NULL;
			m_lastNode = prevNode;

			// If next line not included, prevNode will simply fall out of scope and 
			// get taken care of by the garbage collector. 
			prevNode = NULL;
		}

		m_size = (m_size == 0 ? m_size : m_size - 1); // Prevent negative size
	}
	int GetSize()
	{
		return m_size;
	}
	// ------------ END LINK LIST OPERATIONS ----------------------
private:
	int m_size;					// Holds the size of the link list
	LinkNode<T>* m_root;		// Points to the root fo the link list
	LinkNode<T>* m_lastNode;	// Points to the last node of the link list
};