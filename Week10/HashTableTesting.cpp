#include <iostream>
#include "SeparateChaining.h"

using namespace std;

class PlayerInfo
{
public:
	PlayerInfo() : name(""), score(0) { }
	PlayerInfo(string name, int score)
		: name(name), score(score)
	{}
	const string& GetHashString()
	{
		return name;
	}
	const string& GetName()
	{
		return name;
	}
	int GetScore()
	{
		return score;
	}
private:
	string name;
	int score;
};

int main()
{
	cout << "Separate Chaining example" << endl << endl;

	// Create and fill a hash table
	HashTable<PlayerInfo> hashTable(20);
	PlayerInfo p1("Joe", 11);
	PlayerInfo p2("Pete", 12);
	PlayerInfo p3("Neta", 2);
	PlayerInfo p4("Nate", 30);
	PlayerInfo p5("Jeff", 5);

	hashTable.Insert(p1);
	hashTable.Insert(p2);
	hashTable.Insert(p3);
	hashTable.Insert(p4);
	hashTable.Insert(p5);

	hashTable.Delete(p5);

	PlayerInfo p6;
	// Search for inserted items
	if (hashTable.Find("Nate", &p6))
	{
		cout << "Item: Nate has a score of " << p6.GetScore() << ". " << endl;
	}
	else
	{
		cout << "Item not found";
	}

	return 0;
}