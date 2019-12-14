#ifndef _HEAP_H_
#define _HEAP_H_

#include <vector>

using namespace std;

template<class T>
class Heap
{
   public:
      Heap()
      {

      }

	  // Allows minimum size to be specified
      Heap(int minSize)
      {
         m_heap.reserve(minSize);
      }

	  // Inserting an element into the end of the array
	  // "Bubbles" up the value to the correct position
      void push(T key)
      {
		  // Push to the back of the array (m_heap)
		  m_heap.push_back(key);

		  // Compare the inserted key with the parent node and swap if need be.
		  int index = (int)m_heap.size() - 1;		// Set 'index' to point to the last element
		  T temp = m_heap[index];					// Store a copy of the last element in temp
		  int parentIndex = (index - 1) / 2;		// Find the parent index of any child index

		  // Excute until we find the best position for the inserted element, or the loop ends
		  // Swapping while we traverse upwards through the heap
		  while (index > 0 && temp >= m_heap[parentIndex])
		  {
			  // Bubbling up through the heap
			  m_heap[index] = m_heap[parentIndex];	// Sets the element at index equal to the element at parentIndex
			  index = parentIndex;					// Reposition index at parentIndex
			  parentIndex = (index - 1) / 2;		// Finds the new parentIndex
		  }

		  // Set the pushed value into the correct location within the heap
		  m_heap[index] = temp;
      }
	  
	  // Pop works from the top downwards
	  // Remove the top element by replacing it with the last element of the heap.
	  // It will then propogate the new top element down through the heap.
	  // This will ensure that the next highest value sits at the top of the heap. 
      void pop()
      {
		  int index = 0;

		  // Replace the top element with the last element of the array. Pop the last element off
		  m_heap[index] = m_heap[(int)m_heap.size() - 1];
		  m_heap.pop_back();

		  // Check if we still have a heap to propogate through
		  if (m_heap.size() > 0)
		  {
			  // Restructing the heap such that the largest item is at the top
			  // -------------------------------------------------------------

			  T temp = m_heap[index];		// Stores the new top item that will be propogated down.
			  int currentIndex = 0, leftIndex = 0, rightIndex = 0;

			  // Check which side of the node we are traversing down
			  // Traversal
			  while (index < (int)m_heap.size() / 2)
			  {
				  // Calculate the left index and right index of any element (if they exist)
				  leftIndex = 2 * index + 1;	// Returns the left child index of any parent index
				  rightIndex = leftIndex + 1;	// Returns the right child index

				  // Which side of the parent node are we going down?
				  if (rightIndex < (int)m_heap.size() && m_heap[leftIndex] < m_heap[rightIndex])
				  {
					  // Traverse right
					  currentIndex = rightIndex;
				  }
				  else
				  {
					  // Traverse left
					  currentIndex = leftIndex;
				  }

				  // Is there a case where I need to exit out of this loop early?
				  // When my temp is greater than what my currentIndex is pointing too.
				  if (temp >= m_heap[currentIndex])
				  {
					  break;
				  }

				  // ...otherwise, we have to iterate once again.
				  // Set value to move elements upwards through the tree
				  m_heap[index] = m_heap[currentIndex];
				  index = currentIndex;
			  }

			  // Assign the node (store in temp) to the correct position
			  m_heap[index] = temp;
		  }
      }

	  T peek()
      {
         return m_heap[0];
      }

      int size()
      {
         return (int)m_heap.size();
      }

   private:
      vector<T> m_heap;
};

#endif