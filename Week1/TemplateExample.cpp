#include <iostream>
using namespace std;

// Check 2 numbers. Return the smallest
template <class T>
T min_func(T lVal, T rVal)
{
	if (lVal > rVal)
	{
		return rVal;
	}
	return lVal;
}

// Check 2 numbers. Return the largest
template <class T>
T max_func(T lVal, T rVal)
{
	if (lVal < rVal)
	{
		return rVal;
	}
	return lVal;
}

template <class T>
class TemplateClass
{
public:
	TemplateClass(T val)
	{
		m_val = val;
	}
	bool operator<(TemplateClass& rVal)
	{
		return m_val < rVal.GetVal();
	}
	bool operator>(TemplateClass& rVal)
	{
		return m_val > rVal.GetVal();
	}
	T GetVal()
	{
		return m_val;
	}
private:
	T m_val;
};
/*
int main()
{
	cout << "Template Example" << endl << endl;
	cout << "Min = " << min_func(30, 26) << endl;
	cout << "Max = " << max_func(56.1, 43.6) << endl;

	cout << "Max (objects) = " << max_func(TemplateClass<int>(7), TemplateClass<int>(4)).GetVal();

	return 0;
}
*/