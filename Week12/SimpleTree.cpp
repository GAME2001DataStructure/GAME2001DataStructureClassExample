#include <iostream>

using namespace std;

class Node
{
   public:
      Node(int obj) : m_object(obj), m_next(NULL),
                      m_prev(NULL), m_child(NULL)
      {
         cout << "Node created!" << endl;
      }

      ~Node()
      {
		  m_prev = NULL;

		  if (m_child != NULL)
		  {
			  // I HAVE CHILDREN!!
			  delete m_child;
		  }

		  if (m_next != NULL)
		  {
			  // I HAVE SIBLINGS!!
			  delete m_next;
		  }

		  m_child = NULL;
		  m_next = NULL;

		  cout << "Node: " << m_object << " destroyed" << endl;
      }

      void AddChild(Node *node)
      {
		  // Check if this node does not have a child
		  if (m_child == NULL)
		  {
			  // No child node
			  m_child = node;
		  }
		  else
		  {
			  // Has child node. Call AddSibling on that child
			  m_child->AddSibling(node);
		  }
      }

      void AddSibling(Node *node)
      {
		  Node* ptr = m_next;

		  if (m_next == NULL)
		  {
			  // No more siblings. Add my node.
			  m_next = node;
			  node->m_prev = this;	
		  }
		  else
		  {
			  // Traversal across (potentially) multiple siblings
			  while (ptr->m_next != NULL)
			  {
				  // Moves the pointer to the next sibling
				  ptr = ptr->m_next;
			  }

			  // Add new sibling to the end of siblings
			  ptr->m_next = node;
			  node->m_prev = ptr;
		  }
      }

	  // "Recursively" display each node of the tree
      void DisplayTree()
      {
		  cout << m_object;


		  // Does this node have siblings?
		  if (m_next != NULL)
		  {
			  cout << " ";
			  m_next->DisplayTree();
		  }

		  // Does this node have children?
		  if (m_child != NULL)
		  {
			  cout << endl;
			  m_child->DisplayTree();
		  }
      }

	  // SLOW! Linear search
      bool Search(int value)
      {
		  // Pseudo base-case
		  if (m_object == value)
		  {
			  // I found my node!
			  return true;
		  }

		  // I have not found my node. Check children, check siblings.
		  // Check Children
		  if (m_child != NULL)
		  {
			  // I have children
			  if (m_child->Search(value) == true)
			  {
				  return true;
			  }
		  }

		  // Check Siblings
		  if (m_next != NULL)
		  {
			  // I have siblings
			  if (m_next->Search(value) == true)
			  {
				  return true;
			  }
		  }
		  // Did not find the value being searched.
		  return false;
      }

   private:
      int m_object;
      Node *m_next, *m_prev, *m_child;
};

/*
int main(int args, char *arg[])
{
   cout << "Simple Tree Data Structure" 
	    << endl << endl;

   // Manually create the tree...
   Node *root = new Node(1);
   Node *subTree1 = new Node(3);

   root->AddChild(new Node(2));

   subTree1->AddChild(new Node(5));
   subTree1->AddChild(new Node(6));

   root->AddChild(subTree1);
   root->AddChild(new Node(4));

   cout << endl;

   // Display the tree...
   cout << "Tree contents by level:" << endl;
   root->DisplayTree();
   cout << endl << endl;

   // Test searching...
   cout << "Searching for node 5: ";

   if(root->Search(5) == true)
      cout << "Node Found!" << endl;
   else
      cout << "Node NOT Found!" << endl;

   cout << "Searching for node 9: ";

   if(root->Search(9) == true)
      cout << "Node Found!" << endl;
   else
      cout << "Node NOT Found!" << endl;

   cout << endl;


   // Will delete entire tree...
   delete root;

   cout << endl << endl;

   return 1;
}
*/