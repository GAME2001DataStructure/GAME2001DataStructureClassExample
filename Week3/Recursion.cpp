#include <iostream>
using namespace std;

// Printing down from a given number until we reach 1

void PrintNumReverse(int x)
{
	// Base case
	if (x <= 0)
	{
		return;
	}

	cout << " " << x;

	// Tail Recursion
	PrintNumReverse(x - 1);
}
/*
int main()
{
	cout << "Recursion Example" << endl;
	cout << "Here is a recursive call: " << endl;

	// Call a recursive function
	PrintNumReverse(20);

	return 1;
}
*/