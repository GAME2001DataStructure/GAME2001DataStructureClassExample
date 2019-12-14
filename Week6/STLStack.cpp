// Example of using an STL stack
#include <iostream>
#include <stack>
#include <vector>
#include <list>

using namespace std;

// Template function that prints a stack
template <class T>
void DisplayStack(T& stack)
{
	cout << "(Size - " << stack.size() << ") :";

	while (stack.empty() == false)
	{
		cout << " " << stack.top();
		stack.pop();
	}

	cout << endl;
}

int main()
{
	cout << "STL Stacks Example" << endl << endl;

	stack<int> intStack;				// Default stacks. Uses a deque (pronounced: "deck" or "deek")
	stack<int, vector<int>> vecStack;	// Creates a stack using a vector<int>
	stack<int, list<int>> listStack;	// Creates a stack using a list<int>

	for (int i = 0; i < 5; i++)
	{
		intStack.push(11 + i);
		vecStack.push(22 + i);
		listStack.push(33 + i);
	}

	// Display all the stacks
	cout << "Contents of the int stack: ";
	DisplayStack(intStack);

	cout << "Contents of the vector stack: ";
	DisplayStack(vecStack);

	cout << "Contents of the list stack: ";
	DisplayStack(listStack);

	return 0;
}