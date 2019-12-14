#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include <vector>
#include <stack>
#include <queue>
#include <cassert>

using namespace std;

template<typename T>
class GraphVertex
{
public:
	GraphVertex(T node) : m_node(node) { }

	T GetNode() { return m_node; }

private:
	T m_node;
};

template<typename T>
class Graph
{
public:
	Graph(int numVerts) 
		: m_maxVerts(numVerts), 
		m_adjMatrix(NULL)
	{
		assert(numVerts > 0);

		m_vertices.reserve(m_maxVerts);

		m_adjMatrix = new char*[m_maxVerts];
		assert(m_adjMatrix != NULL);

		m_vertVisits = new char[m_maxVerts];
		assert(m_vertVisits != NULL);

		memset(m_vertVisits, 0, m_maxVerts);

		for(int i = 0; i < m_maxVerts; i++)
		{
			m_adjMatrix[i] = new char[m_maxVerts];
			assert(m_adjMatrix[i] != NULL);

			memset(m_adjMatrix[i], 0, m_maxVerts);
		}
	}

	~Graph()
	{
		if(m_adjMatrix != NULL)
		{
			for(int i = 0; i < m_maxVerts; i++)
			{
				if(m_adjMatrix[i] != NULL)
				{
					delete[] m_adjMatrix[i];
					m_adjMatrix[i] = NULL;
				}
			}

			delete[] m_adjMatrix;
			m_adjMatrix = NULL;
		}

		if(m_vertVisits != NULL)
		{
			delete[] m_vertVisits;
			m_vertVisits = NULL;
		}
	}

	bool push(T node)
	{
		// Check to see if we have space to push a new vertex (node)
		if ((int)m_vertices.size() >= m_maxVerts)
		{
			// Not enough space to push new vertex (node)
			return false;
		}

		// We have space to push a new vertex (node)
		m_vertices.push_back(GraphVertex<T>(node));
		return true;
	}
	
	// Bidirectional Traversal
	void attachEdge(int index1, int index2)
	{
		assert(m_adjMatrix != NULL);

		// Fill out the adjacency matrix to mark a connected vertex (node)
		// Nondirectional edge (2 way).
		m_adjMatrix[index1][index2] = 1;
		m_adjMatrix[index2][index1] = 1;
	}

	// One-way
	void attachDirectedEdge(int index1, int index2)
	{
		assert(m_adjMatrix != NULL);

		// Fill out the adjacency matrix to mark a connected vertex (node)
		// Directional
		m_adjMatrix[index1][index2] = 1;
	}

	int getNextUnvisitedVertex(int index)
	{
		assert(m_adjMatrix != NULL);
		assert(m_vertVisits != NULL);

		// Traverse through all vertices of the graph
		for (int i = 0; i < (int)m_vertices.size(); i++)
		{
			// Check if a connection between 'index' and 'i' exists.
			// Check if the vertex at 'i' has not been checked.
			if (m_adjMatrix[index][i] == 1 && m_vertVisits[i] == 0)
			{
				return i;
			}
		}

		// All adjanct vertices have been visited.
		return -1;
	}

	// Traversing down a path until destination is reached or none is found.
	// Stack gets popped back until another path is found.
	bool DepthFirstSearch(int startIndex, int endIndex)
	{
		assert(m_adjMatrix != NULL);
		assert(m_vertVisits != NULL);

		// We've visited our first vertex (node)
		m_vertVisits[startIndex] = 1;

		// FOR OUTPUT PURPOSES ONLY
		cout << m_vertices[startIndex].GetNode();

		stack<int> searchStack;
		int vert = 0;

		// Push the visited vertex onto the stack
		searchStack.push(startIndex);

		// When the stack is empty OR, we have found our destination, we are done.
		while (searchStack.empty() != true)
		{
			// Get the next unvisited vertex
			vert = getNextUnvisitedVertex(searchStack.top());

			if (vert == -1)
			{
				searchStack.pop();
			}
			else
			{
				// New unvisited vertex found
				m_vertVisits[vert] = 1;

				// FOR OUTPUT PURPOSES ONLY.
				cout << m_vertices[vert].GetNode();

				searchStack.push(vert);
			}

			if (vert == endIndex)
			{
				// Found my destination!
				memset(m_vertVisits, 0, m_maxVerts);	// "Reset" of m_vertVisits. All values eqaul to 0
				return true;
			}
		}

		memset(m_vertVisits, 0, m_maxVerts); // "Reset"
		return false;	// Path to destination not found from startIndex.
	}

	// Searches all adjacent vertices first before moving on.
	// Queue data structure used. 
	bool BreadthFirstSearch(int startIndex, int endIndex)
	{
		assert(m_adjMatrix != NULL);
		assert(m_vertVisits != NULL);

		// We are visiting our first vertex (startIndex)
		m_vertVisits[startIndex] = 1;

		// FOR OUTPUT PURPOSES
		cout << m_vertices[startIndex].GetNode();

		queue<int> searchQueue;
		int vert1 = 0, vert2 = 0;

		// Push our visited vertex to the queue.
		searchQueue.push(startIndex);

		// Keep traversing until our searchQueue is empty OR we find our destination
		while (searchQueue.empty() != true)
		{
			// Save the front of the queue to vert1
			vert1 = searchQueue.front();
			searchQueue.pop();

			// Have we reached our destination. 
			if (vert1 == endIndex)
			{
				// Destination is found!
				memset(m_vertVisits, 0, m_maxVerts);
				return true;
			}

			// Traverse down to all adjacent nodes
			while((vert2 = getNextUnvisitedVertex(vert1)) != -1)
			{
				// Visited the vertex at index vert2
				m_vertVisits[vert2] = 1;

				// FOR OUTPUT PURPOSES
				cout << m_vertices[vert2].GetNode();

				searchQueue.push(vert2);
			}
		}

		memset(m_vertVisits, 0, m_maxVerts);
		return false;
	}

private:
	vector<GraphVertex<T> > m_vertices;	// Graph object (array)
	int m_maxVerts;	// Max number of vertices allowed

	char **m_adjMatrix;		// Pointer to a 2D array ( Adjacency Matrix )
	char *m_vertVisits;		// Pointer to an array	( Verticies visited )
};

#endif