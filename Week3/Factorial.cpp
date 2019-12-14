#include <iostream>
#include <cassert>
using namespace std;

// Single factorial
int factorial(int x)
{
	assert(x >= 0);

	// Base case
	if (x == 0)
	{
		return 1;
	}

	return(factorial(x - 1) * x);
}

// Double factorial
int doubleFactorial(int x)
{
	assert(x >= 0);

	// Base Case
	if (x == 0 || x == 1)
	{
		return 1;
	}

	// Tail Recursion
	return(doubleFactorial(x - 2) * x);
}
/*
int main()
{
	cout << "Factorials!!!!" << endl;

	cout << "The factorials of 5: ";
	// Call single factorial function
	cout << factorial(5) << endl;

	cout << "The double factorial of 7 is: ";
	cout << doubleFactorial(7) << endl;
}
*/