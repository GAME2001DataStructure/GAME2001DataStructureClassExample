#include <iostream>
#include "DoublyLinkList.h"

using namespace std;


int main()
{
	cout << "Doubly Link List Example" << endl << endl;

	LinkList<int> lList;

	lList.Push(101);
	lList.Push(101);
	lList.Push(101);
	lList.Push(101);
	lList.Push(101);
	lList.Pop_Front();
	lList.Push(201);

	LinkIterator<int> it;

	cout << "Contents of the link list (forward):";
	for (it = lList.Begin(); it != lList.End(); it++)
	{
		cout << " " << *it;
	}

	cout << endl << endl;

	cout << "Contents of the link list (reverse): ";
	for (it = lList.Last(); it != NULL; it--)
	{
		cout << " " << *it;
	}

	cout << endl << endl;

	return 0;
}
