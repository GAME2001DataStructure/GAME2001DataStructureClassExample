#include <iostream>
#include "PriorityQueue.h"

using namespace std;

template<class T>
class less_cmp
{
public:
	inline bool operator()(T lVal, T rVal)
	{
		return (lVal < rVal);
	}
};

template<class T>
class less_cmp_ptr
{
public:
	inline bool operator()(T lVal, T rVal)
	{
		return ((*lVal) < (*rVal));
	}
};

template<class T>
class greater_cmp
{
public:
	inline bool operator()(T lVal, T rVal)
	{
		return !(lVal < rVal);
	}
};

template<class T>
class greater_cmp_ptr
{
public:
	inline bool operator()(T lVal, T rVal)
	{
		return !((*lVal) < (*rVal));
	}
};

class NetworkMessage
{
public:
	// Constructors and destructor
	NetworkMessage() : m_priority(0), m_id(0) { }
	NetworkMessage(int p, int id) : m_priority(p), m_id(id) { }
	~NetworkMessage() { }

	// Get Methods
	int GetPriority()
	{
		return m_priority;
	}
	int GetID()
	{
		return m_id;
	}
	// Overloaded operators ( < and > )
	bool operator<(NetworkMessage& m)
	{
		// Check against both priority and id values
		if (m_priority < m.GetPriority())
		{
			return true;
		}
		else if (m_id < m.GetID())
		{
			return true;
		}

		return false;
	}
	bool operator>(NetworkMessage& m)
	{
		return !(*this < m);
	}
private:
	int m_priority, m_id;
};

int main()
{
	cout << "Priority Queue Data Structure Examples " << endl << endl;

	const int size = 4;
	PriorityQueue<NetworkMessage, less_cmp<NetworkMessage> > que(size);

	que.push(NetworkMessage(3, 100));
	que.push(NetworkMessage(2, 286));
	que.push(NetworkMessage(1, 362));
	que.push(NetworkMessage(3, 435));

	// Display priority queue
	cout << "Priority queue content (Size - " << que.GetSize() << ") : " << endl;

	while (que.isEmpty() == false)
	{
		cout << "   Priority: " << que.front().GetPriority();
		cout << "   ID: " << que.front().GetID();
		cout << endl;

		que.pop();
	}

	cout << endl;

	if (que.isEmpty() == true)
	{
		cout << "The container is empty" << endl;
	}
	else
	{
		cout << "The container is NOT empty" << endl;
	}

	return 1;
}
