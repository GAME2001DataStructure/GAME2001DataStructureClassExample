#ifndef _BINARY_TREE_
#define _BINARY_TREE_

#include <iostream>

using namespace std;

template<typename T>
class BinaryTree;

template<typename T>
class Node
{
   friend class BinaryTree<T>;

   public:
      Node(T key) : m_key(key), m_left(NULL), m_right(NULL)
      {

      }

      ~Node()
      {
         if(m_left != NULL)
         {
           delete m_left;
           m_left = NULL;
         }

         if(m_right != NULL)
         {
           delete m_right;
           m_right = NULL;
         }
      }

      T GetKey()
      {
         return m_key;
      }

   private:
      T m_key;
      Node *m_left, *m_right;
};

template<typename T>
class BinaryTree
{
   public:
      BinaryTree() : m_root(NULL)
      {

      }

      ~BinaryTree()
      {
         if(m_root != NULL)
         {
           delete m_root;
           m_root = NULL;
         }
      }
	  // Check if the root node exists
	  // Traversal to the left or right of nodes based on the key
      // Attach the new node
	  // All paths must return a value
      bool push(T key)
      {
		  // Create the new node to be added to the tree
		  Node<T>* newNode = new Node<T>(key);

		  // Check if the root node exists
		  if (m_root == NULL)
		  {
			  // Root node does not exists. Newnode will become the root
			  m_root = newNode;
		  }
		  else
		  {
			  // Root node does exists. Traverse down the tree
			  Node<T>* parentNode = NULL;
			  Node<T>* currentNode = m_root;

			  // Traversal
			  while (1)
			  {
				  parentNode = currentNode;

				  // Managing duplicates.
				  // IN THIS IMPLEMENTATION. No duplicates allowed. 
				  if (key == currentNode->m_key)
				  {
					  // Duplicate found! Delete it.
					  delete newNode;
					  return false;
				  }

				  // Do I traverse left or right?
				  if (key < currentNode->m_key)
				  {
					  // GO LEFT
					  currentNode = currentNode->m_left;

					  if (currentNode == NULL)
					  {
						  // This is where the newNode must go
						  parentNode->m_left = newNode;
						  return true;
					  }
				  }
				  else
				  {
					  // GO RIGHT!
					  currentNode = currentNode->m_right;

					  if (currentNode == NULL)
					  {
						  // This is where the newNode must go
						  parentNode->m_right = newNode;
						  return true;
					  }
				  }
			  }
		  }

		  return true;
      }

	  // Check if the root exists
	  // Traverse the tree until key is found or not found
      bool search(T key)
      {
		  if (m_root == NULL)
		  {
			  return false;
		  }

		  Node<T>* currentNode = m_root;		// Node pointer used to traverse through the tree

		  while (currentNode->m_key != key)		// Keep traversing so long as the currentNode key doesn't equal the search key
		  {
			  // Left vs right
			  if (key < currentNode->m_key)
			  {
				  // Go left
				  currentNode = currentNode->m_left;
			  }
			  else
			  {
				  // Go right
				  currentNode = currentNode->m_right;
			  }

			  // Did not find the search key in the tree
			  if (currentNode == NULL)
			  {
				  return false;
			  }
		  }

		  // Search key exists in the tree
		  return true;
      }

	  // 0. Check if the root exists
	  // 1. No children
	  // 2. One child
	  // 3. Two children
	  void remove(T key)
	  {
		  // Check if the root exists
		  if (m_root == NULL)
		  {
			  return;
		  }

		  Node<T>* parent = m_root;
		  Node<T>* node = m_root;
		  bool isLeftNode = false;

		  // Traverse and find the key to be removed
		  while (node->m_key != key)
		  {
			  parent = node;

			  // Left vs right
			  if (key < node->m_key)
			  {
				  // Left
				  node = node->m_left;
				  isLeftNode = true;
			  }
			  else
			  {
				  // Right
				  node = node->m_right;
				  isLeftNode = false;
			  }

			  // Node not found. Get out of here
			  if (node == NULL)
			  {
				  return;
			  }
		  }
		  // ---------------------- Removal Work -----------------------
		  // 1. No children?
		  if (node->m_left == NULL && node->m_right == NULL)
		  {
			  // NO CHILDREN!
			  // Is this the root?
			  if (node == m_root)
			  {
				  // This is the root!
				  m_root = NULL;
			  }
			  else if (isLeftNode == true)
			  {
				  // This is the left side of the parent node
				  parent->m_left = NULL;
			  }
			  else
			  {
				  // This is the right side of the parent node
				  parent->m_right = NULL;
			  }
		  }
		  else if (node->m_left == NULL) // 2a. One child (right exists)
		  {
			  // Check the root
			  if (node == m_root)
			  {
				  // Right node is now the new root node
				  m_root = node->m_right;
			  }
			  else if (isLeftNode == true)
			  {
				  // Child is to the left of the parent.
				  parent->m_left = node->m_right;
			  }
			  else
			  {
				  // Child is to the right of the parent
				  parent->m_right = node->m_right;
			  }
		  }
		  else if (node->m_right == NULL) // 2b. One child (left exists)
		  {
			  // Check the root
			  if (node == m_root)
			  {
				  // Left node is now the new root node
				  m_root = node->m_left;
			  }
			  else if (isLeftNode == true)
			  {
				  // Child is to the left of the parent
				  parent->m_left = node->m_left;
			  }
			  else
			  {
				  // Child is to the right of the parent
				  parent->m_right = node->m_left;
			  }
		  }
		  else // 3. Two children
		  {
			  Node<T>* tempNode = node->m_right;
			  Node<T>* successor = node;
			  Node<T>* successorParent = node;

			  // Traversal down the right side of the node to be deleted hanging left
			  while (tempNode != NULL)
			  {
				  successorParent = successor;
				  successor = tempNode;
				  tempNode = tempNode->m_left;
			  }

			  if (successor != node->m_right)
			  {
				  successorParent->m_left = successor->m_right;
				  successor->m_right = node->m_right;
			  }

			  // Assign the success to the node to be removed
			  // Check the root
			  if (node == m_root)
			  {
				  m_root = successor;
			  }
			  else if (isLeftNode)
			  {
				  node = parent->m_left;
				  parent->m_left = successor;
			  }
			  else
			  {
				  node = parent->m_right;
				  parent->m_right = successor;
			  }

			  successor->m_left = node->m_left;
		  }

		  node->m_left = NULL;
		  node->m_right = NULL;
		  delete node;
	  }

      void DisplayPreOrder()
      {
         DisplayPreOrder(m_root);
      }

      void DisplayPostOrder()
      {
         DisplayPostOrder(m_root);
      }

      void DisplayInOrder()
      {
         DisplayInOrder(m_root);
      }

   private:
	   // Node, Left child, right child
      void DisplayPreOrder(Node<T> *node)
      {
         if(node != NULL)
         {
           cout << node->m_key << " ";

           DisplayPreOrder(node->m_left);
           DisplayPreOrder(node->m_right);
         }
      }

	  // Left child, right child, node
      void DisplayPostOrder(Node<T> *node)
      {
         if(node != NULL)
         {
           DisplayPostOrder(node->m_left);
           DisplayPostOrder(node->m_right);

           cout << node->m_key << " ";
         }
      }

	  // Left child, Node, right child
      void DisplayInOrder(Node<T> *node)
      {
         if(node != NULL)
         {
           DisplayInOrder(node->m_left);

           cout << node->m_key << " ";

           DisplayInOrder(node->m_right);
         }
      }

   private:
      Node<T> *m_root;
};

#endif