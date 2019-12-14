#include <iostream>
#include "UnorderedArray.h"

using namespace std;

int main()
{
	cout << "Merge Sort Algorithm" << endl;

	UnorderedArray<int> array(5);
	array.push(80);
	array.push(64);
	array.push(99);
	array.push(76);
	array.push(5);

	UnorderedArray<float> arr2(10);
	arr2.push(30.5);

	cout << "Before sort: ";

	for (int i = 0; i < 5; i++)
	{
		cout << " " << array[i];
	}

	cout << endl;

	array.MergeSort();

	cout << "After sort: ";

	for (int i = 0; i < 5; i++)
	{
		cout << " " << array[i];
	}
	cout << endl << endl;

	system("pause");
	return 1;
}