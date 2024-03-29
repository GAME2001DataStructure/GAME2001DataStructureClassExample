#ifndef _HEAP_H_
#define _HEAP_H_

#include <vector>

using namespace std;

template<typename KEY, typename CMP>
class Heap
{
public:
	Heap()
	{

	}

	Heap(int minSize)
	{
		m_heap.reserve(minSize);
	}

	void push(KEY key)
	{
		m_heap.push_back(key);

		int index = (int)m_heap.size() - 1;
		KEY temp = m_heap[index];
		int parentIndex = (index - 1) / 2;

		CMP cmp;

		while(index > 0 && (cmp(temp, m_heap[parentIndex]) ||
			temp == m_heap[parentIndex]))
		{
			m_heap[index] = m_heap[parentIndex];
			index = parentIndex;
			parentIndex = (parentIndex - 1) / 2;
		}

		m_heap[index] = temp;
	}

	void pop()
	{
		int index = 0;

		m_heap[index] = m_heap[(int)m_heap.size() - 1];
		m_heap.pop_back();

		if (m_heap.size() > 0)
		{
			KEY temp = m_heap[index];

			int currentIndex = 0, leftIndex = 0, rightIndex = 0;

			while(index < (int)m_heap.size() / 2)
			{
				leftIndex = 2 * index + 1;
				rightIndex = leftIndex + 1;

				CMP cmp;

				if(rightIndex < (int)m_heap.size() &&
					(cmp(m_heap[rightIndex], m_heap[leftIndex]) ||
					m_heap[rightIndex] == m_heap[leftIndex]))
				{
					currentIndex = rightIndex;
				}
				else
				{
					currentIndex = leftIndex;
				}

				if(cmp(temp, m_heap[currentIndex]) ||
					temp == m_heap[currentIndex])
					break;

				m_heap[index] = m_heap[currentIndex];
				index = currentIndex;
			}

			m_heap[index] = temp;
		}
	}

	KEY peek()
	{
		return m_heap[0];
	}

	int size()
	{
		return (int)m_heap.size();
	}

private:
	vector<KEY> m_heap;
};

#endif