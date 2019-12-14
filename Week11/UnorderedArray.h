#pragma once
#include <cassert>

#define QUICKSORT_CUTOFF 4

template <class T>
class UnorderedArray
{
public:
	// Constructor
	UnorderedArray(int size, int growBy = 1) :
		m_array(NULL), m_maxSize(0),
		m_growSize(0), m_numElements(0)
	{
		if (size)
		{
			m_maxSize = size;
			m_array = new T[m_maxSize];
			memset(m_array, 0, sizeof(T) * m_maxSize);

			m_growSize = ((growBy > 0) ? growBy : 0); // Ternary statement -- Glorified if-statement
		}
	}
	// Destructor
	~UnorderedArray()
	{
		if (m_array != NULL)
		{
			delete[] m_array;
			m_array = NULL;
		}
	}
	// Insertion
	// Fast insertion for unorderedarray -- Big-O of O(1)
	void push(T val)
	{
		assert(m_array != NULL); // Debugging purposes

		if (m_numElements >= m_maxSize)
		{
			Expand();
		}

		m_array[m_numElements] = val;
		m_numElements++;
	}
	// Deletion (2 methods)
	// Removes the last item that was inserted
	void pop()
	{
		if (m_numElements > 0)
		{
			m_numElements--;
		}
	}
	// Remove an item given an index
	// (Almost) Brute-force execution -- Big-O = O(N)
	void remove(int index)
	{
		assert(m_array != NULL);

		if (index >= m_numElements)
		{
			return;
		}

		for (int i = index; i < m_numElements; i++)
		{
			if (i + 1 < m_numElements)
			{
				m_array[i] = m_array[i + 1];
			}
		}
		m_numElements--;
	}
	// Overload the [] operator
	T& operator[](int index)
	{
		assert(m_array != NULL && index < m_numElements);
		return m_array[index];
	}
	// Search (Linear search) -- Big-O = O(N)
	int search(T val)
	{
		assert(m_array != NULL);

		// Brute-force Search
		for (int i = 0; i < m_numElements; i++)
		{
			if (m_array[i] == val)
				return i;
		}
		return -1;
	}
	// ----------- SORTING ALGORITHMS ---------------
	// ---------- PARTITIONING ---------------------
	void SwapElements(int index1, int index2)
	{
		assert(index1 >= 0 && index1 < m_numElements);
		assert(index2 >= 0 && index2 < m_numElements);
		assert(m_array != NULL);

		T temp = m_array[index1];
		m_array[index1] = m_array[index2];
		m_array[index2] = temp;
	}
	void QuickSort()
	{
		QuickSort(0, m_numElements - 1);
	}
	/*
	int Partition(T pivot)
	{
		return Partition(0, m_numElements - 1, pivot);
	}
	int Partition(int lIndex, int rIndex, T pivot)
	{
		int currentLeft = lIndex;
		int currentRight = rIndex;

		while (1)
		{
			// Traverse from left to right
			while (currentLeft < rIndex && m_array[currentLeft] < pivot)
			{
				// m_array[currentLeft] is smaller than the pivot
				// Increment my currentLeft by 1 to the next element
				currentLeft++;
			}

			// Traverse from right to left
			while (currentRight > lIndex && m_array[currentRight] > pivot)
			{
				// m_array[currentRight] is greater than the pivot
				// Decrement my currentRight by 1 to the next element
				currentRight--;
			}

			if (currentLeft >= currentRight)
			{
				// Done with partitioning. No more searching.
				break;
			}

			// Swap elements
			SwapElements(currentLeft, currentRight);
		}

		// Returns the position of the pivot
		return currentLeft;
	}
	*/
	
	// --------- SHELL SORT ----------------------
	void Shellsort()
	{
		assert(m_array != NULL);
		
		T temp;
		int i = 0, k = 0;

		// Sequence (gap)
		int seq = 1;

		// Determine the gap size with the Knuth method
		while (seq <= m_numElements / 3)
		{
			seq = seq * 3 + 1;
		}

		while (seq > 0)
		{
			for (k = seq; k < m_numElements; k++)
			{
				temp = m_array[k];	// Stores m_array[k] temporarily
				i = k;

				// We want to compare 2 values with a gap of "seq"
				while (i > seq - 1 && m_array[i - seq] >= temp)
				{
					// We need to swap the 2 compared values
					m_array[i] = m_array[i - seq];
					i -= seq;
				}

				m_array[i] = temp;
			}

			// Find the next lower Knuth value
			seq = (seq - 1) / 3;
		}
	}
	// Bubble Sort -- BIG-O = O(N^2)
	void BubbleSort()
	{
		assert(m_array != NULL);

		T temp;

		for (int k = m_numElements - 1; k > 0; k--)
		{
			for (int i = 0; i < k; i++)
			{
				// Comparing 2 adjacent elements 
				if (m_array[i] > m_array[i + 1])
				{
					// Swapping the elements
					temp = m_array[i];
					m_array[i] = m_array[i + 1];
					m_array[i + 1] = temp;
				}
			}
		}
	}
	// Selection Sort -- BIG-O = O(N^2)
	void SelectionSort()
	{
		assert(m_array != NULL);

		T temp;
		int min = 0;

		// The lowest position to swap the smallest element to...
		for (int k = 0; k < m_numElements - 1; k++)
		{
			min = k;

			// Iterate through the array to find the smallest value
			for (int i = k + 1; i < m_numElements; i++)
			{
				if (m_array[i] < m_array[min])
				{
					// Store the index to the smallest element
					min = i;
				}
			}

			// Swapping of the lowest element with the lowest available index
			if (m_array[k] > m_array[min])
			{
				// Swap
				temp = m_array[k];
				m_array[k] = m_array[min];
				m_array[min] = temp;
			}
		}
	}
	// Insertion Sort -- BIG-O = O(N^2)
	void InsertionSort()
	{
		assert(m_array != NULL);

		T temp;
		int i = 0;

		for (int k = 1; k < m_numElements; k++)
		{
			temp = m_array[k];
			i = k;

			// Shifting of elements if necessary. Create a space for an element
			// to be inserted in the correct location.
			while (i > 0 && m_array[i - 1] >= temp)
			{
				// Push elements to the right
				m_array[i] = m_array[i - 1];
				i--;
			}

			m_array[i] = temp;
		}
	}
	// Merge Sort -- BIG-O = O(N logN)
	void MergeSort()
	{
		assert(m_array != NULL);

		T* tempArray = new T[m_numElements];
		assert(tempArray != NULL);

		MergeSort(tempArray, 0, m_numElements - 1);
		delete[] tempArray;
	}
	//------------ END SORTING ----------------------
	// Clear - Big-O = O(1)
	void clear()
	{
		m_numElements = 0;
	}
	// Gets and Sets
	int GetSize() 
	{
		return m_numElements;
	}
	int GetMaxSize()
	{
		return m_maxSize;
	}
	int GetGrowSize()
	{
		return m_growSize;
	}
	void SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}
private:
	// Recursive Quick Sort
	void QuickSort(int lVal, int rVal)
	{
		// Check whether I have enough items to do a quick sort (median 3). 
		// If not, do InsertionSort instead
		if ((rVal - lVal + 1) < QUICKSORT_CUTOFF)
		{
			// Not enough items!
			InsertionSort(lVal, rVal);
			return;
		}

		int center = (lVal + rVal) / 2;

		// Order left, center and right
		if (m_array[lVal] > m_array[center])	// Left vs center
		{
			SwapElements(lVal, center);
		}
		if (m_array[lVal] > m_array[rVal])		// Left vs right
		{
			SwapElements(lVal, rVal);
		}
		if (m_array[center] > m_array[rVal])	// Center vs right
		{
			SwapElements(center, rVal);
		}

		int pivotIndex = Partition(lVal, rVal, center); // Partition based around "center"

		QuickSort(lVal, pivotIndex - 1);	// Quicksort the left half
		QuickSort(pivotIndex, rVal);		// Quicksort the right half
	}
	
	int Partition(int lIndex, int rIndex, int pivot)
	{
		while (1)
		{
			while (m_array[++lIndex] < m_array[pivot]);
			while (m_array[--rIndex] > m_array[pivot]);

			if (lIndex >= rIndex)
				break;

			SwapElements(lIndex, rIndex);
		}

		return lIndex;
	}
	void InsertionSort(int lVal, int rVal)
	{
		assert(m_array != NULL);

		T temp;
		int i = 0;

		for (int k = lVal + 1; k <= rVal; k++)
		{
			temp = m_array[k];
			i = k;

			// Shifting of elements if necessary. Create a space for an element
			// to be inserted in the correct location.
			while (i > lVal && m_array[i - 1] >= temp)
			{
				// Push elements to the right
				m_array[i] = m_array[i - 1];
				i--;
			}

			m_array[i] = temp;
		}
	}
	// Recursive Merge Sort
	void MergeSort(T* tempArray, int lowerBound, int upperBound)
	{
		// Base case
		if (lowerBound == upperBound)
		{
			return;
		}

		// Determine the middle of the array
		int mid = (lowerBound + upperBound) >> 1;

		MergeSort(tempArray, lowerBound, mid);
		MergeSort(tempArray, mid + 1, upperBound);

		// Merge
		Merge(tempArray, lowerBound, mid + 1, upperBound);
	}
	void Merge(T* tempArray, int low, int mid, int upper)
	{
		int tempLow = low, tempMid = mid - 1;
		int index = 0;

		while (low <= tempMid && mid <= upper)
		{
			// Lower of the 2 values is smaller, move it to the tempArray
			if (m_array[low] < m_array[mid]) 
			{
				tempArray[index++] = m_array[low++];
			}
			else
			{
				tempArray[index++] = m_array[mid++];
			}
		}

		while (low <= tempMid)
		{
			tempArray[index++] = m_array[low++];
		}

		while (mid <= upper)
		{
			tempArray[index++] = m_array[mid++];
		}

		// Place the sorted tempArray into the main array in the correct location
		for (int i = 0; i < upper - tempLow + 1; i++)
		{
			m_array[tempLow + i] = tempArray[i];
		}
	}
	// Expansion
	bool Expand()
	{
		if (m_growSize <= 0)
		{
			return false;
		}

		T* temp = new T[m_maxSize + m_growSize];
		assert(temp != NULL);

		memcpy(temp, m_array, sizeof(T) * m_maxSize);

		delete[] m_array;
		m_array = temp;

		m_maxSize += m_growSize;

		return true;
	}
private:
	// Variables
	T* m_array;

	int m_maxSize;		// Maximum size of our array
	int m_growSize;		// Amount the array can grow
	int m_numElements;	// Number of items currently in my array.
};