#pragma once
#include <string>
// --------
#include <list>
// --------
using namespace std;

template<class T>
class HashItem
{
public:
	HashItem() : m_key("") { }
	~HashItem() { }

	// Gets and sets
	string GetKey()
	{
		return m_key;
	}
	void SetKey(string k)
	{
		m_key = k;
	}

	T GetObject()
	{
		return m_obj;
	}
	void SetObj(T obj)
	{
		m_obj = obj;
	}

	// Overload operator 
	// Equivalence operator
	bool operator==(HashItem& item)	// Allow us to compare 2 HashItem's with each other
	{
		if (m_key == item.GetKey())
		{
			return true;
		}

		return false;
	}

	// Assignment operator
	void operator=(HashItem item)
	{
		m_key = item.GetKey();
		m_obj = item.GetObject();
	}
private:
	string m_key;
	T m_obj;
};

template<class T>
class HashTable
{
public:
	// Constructor and Destructor
	HashTable(int size) : m_size(0)
	{
		if (size > 0) // Input validation
		{
			m_size = GetNextPrimeNum(size);
			m_table = new list<HashItem<T>>[m_size];
		}
	}
	~HashTable()
	{
		if (m_table != NULL)
		{
			delete[] m_table;
			m_table = NULL;
		}
	}
	// Private functions
private:
	bool isNumPrime(int val)
	{
		for (int i = 2; (i * i) <= val; i++) // Checks if val is divisible by i
		{
			if ((val % i) == 0)
			{
				return false;
			}
		}

		return true;
	}
	int GetNextPrimeNum(int val)
	{
		int i;

		for (i = val + 1; ; i++) // "Infinite" for loop
		{
			if (isNumPrime(i))	// Checks if 'i' is a prime number
			{
				break;
			}
		}

		return i;
	}
	// Public functions
public:
	// Insert
	void Insert(T& obj)
	{
		HashItem<T> item;
		item.SetKey(obj.GetHashString());
		item.SetObj(obj);

		int hash = HashFunction(obj);
		m_table[hash].push_back(item);
	}
	// Delete
	void Delete(T& obj)
	{
		int hash = HashFunction(obj);

		// Find the beginning of the link list and create an iterator
		list< HashItem<T> > *ptr = &m_table[hash]; // Sets ptr to the address of m_table[hash]
		typename list< HashItem<T> >::iterator it; // Iterator for list<HashItem<T>> link list

		for (it = ptr->begin(); it != ptr->end(); it++)
		{
			// Check the key of the object the iterator is pointing to vs
			// the key passed into the function (obj.GetHashString())
			if (it->GetKey() == obj.GetHashString())
			{
				// Yes, delete this thing
				ptr->erase(it);
				break;
			}
		}
	}
	// Find
	bool Find(string hashString, T* obj)
	{
		int hash = HashFunction(hashString);

		list< HashItem<T> >* ptr = &m_table[hash]; // Sets ptr to the address of m_table[hash]
		typename list< HashItem<T> >::iterator it; // Iterator for list<HashItem<T>> link list

		for (it = ptr->begin(); it != ptr->end(); it++)
		{
			if (it->GetKey() == hashString)	// Compare the key the iterator is pointing to vs hashString
			{
				if (obj != NULL) // Check for null pointer
				{
					*obj = it->GetObject();
				}

				return true;
			}
		}

		return false;
	}
	int HashFunction(T& obj)
	{
		return HashFunction(obj.GetHashString());
	}
	int HashFunction(const string& HashString)
	{
		int hash = 0;

		// Iterate through each character of the HashString and accumulate its value
		for (int i = 0; i < HashString.length(); i++)
		{
			hash += HashString[i];
		}

		return hash % m_size;	// Constrain our hash value to 0 up to m_size
	}
	// ---------------- Double Hashing Functions -------------------------
	int HashFunction2(T& obj)
	{
		return HashFunction2(obj.GetHashString());
	}
	int HashFunction2(const string& HashString)
	{
		int hash = 0;

		for (int i = 0; i < HashString.length(); i++)
		{
			hash = (hash * 256 + HashString[i]) % m_size;
		}

		return hash;
	}
	// ------------- End Double Hashing Functions ------------------------
	int GetSize()
	{
		return m_size;
	}
private:
	list< HashItem<T> >* m_table;	// Defines a pointer to the beginning of an array of hash item link lists
	int m_size;	// Size of the hash table
};