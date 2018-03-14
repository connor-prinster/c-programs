#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
using namespace std;

int nextPrime(int n);
bool isPrime(int n);

enum Status { ACTIVE, EMPTY, DELETED };

// We store two things.  The key itself and the record associated with the key.
// In our case, the HashKey will be a string.  The HashRecord will be a node containing the word, the count, an a vector of succesor information.
template <typename HashKey, typename HashRecord>
class HashEntry
{
public:
	HashKey key;
	HashRecord * rec;
	Status info;

	HashEntry(HashRecord * hr = NULL, const HashKey & e = HashKey{}, Status i = EMPTY)
		: key{ e }, rec{ hr }, info{ i } { }

};

template <typename HashKey, typename HashRecord>
class HashTable
{
public:
	bool remove(const HashKey & x);										//removes the hashkey
	bool isEmpty() { return activeElements == 0; }						//checks to see if table is empty
	HashRecord * insert(const HashKey x, HashRecord * h);				//insets hashkey
	explicit HashTable(int size = 977) : hashTable(nextPrime(size))
	{
		makeEmpty();
	};
	HashRecord *find(const HashKey & x) const;
	void makeEmpty();
	std::string toString(int howMany = 50);

private:
	vector<HashEntry<HashKey, HashRecord>> hashTable;
	int activeElements;
	bool isActive(int currentPos) const;
	size_t customHash1(const HashKey & x) const;
	size_t customHash2(const HashKey & x) const;
	int findPos(const HashKey & x) const;
	void rehash();
};

// Convert the Hash table to a string.  Since the hashtable is large, HowMany indicates how many entries will be displayed.  
template <typename HashKey, typename HashRecord>
std::string HashTable<HashKey, HashRecord>::toString(int howMany)
{
	int ct = 0;
	stringstream ss;
	ss << "Current size " << hashTable.size() << endl;
	for (int i = 0; i < hashTable.size() && ct < howMany; i++)
		if (hashTable[i].info == ACTIVE){
		     ss << hashTable[i].rec->toString() << "\n";
		     ct++;
		}
	return ss.str();

}

//===========================//
//IMPLEMENTING DOUBLE HASHING//
//=================================================================================
// return the subscript where x is located in the hash table.    
template <typename HashKey, typename HashRecord>
int HashTable<HashKey, HashRecord>::findPos(const HashKey & x) const
{
	int offset = 1;
	int iteration = 0;
	int origPos = customHash1(x);
	int index = origPos;
	int customStep = customHash2(x);

	while (hashTable[index].info != EMPTY && hashTable[index].key != x)
	{
		index += offset;  // Compute ith probe
		iteration = offset++ * customStep;                     
		if (index >= (int)hashTable.size())    // Cheaper than  mod
			index -= hashTable.size();

		if ((origPos + iteration) > hashTable.size())
		{
			index = (origPos + iteration) % hashTable.size();
		}
		else
		{
			index = origPos + iteration;
		}
	}

	return index;
};
//=================================================================================
//							 //
//===========================//

// Remove all elements of the table by setting status to empty.
// Have you seen the range based loop for accessing elements of a vector?
// for (auto &entry:hashTable) says, let a reference variable "entry" iterate through all entries of the hashTable vector
// The "auto" part says to figure out the type of the element automatically (based on what is passed in).
template <typename HashKey, typename HashRecord>
void HashTable<HashKey, HashRecord>::makeEmpty()
{
	activeElements = 0;
	for (auto & entry : hashTable)
		entry.info = EMPTY;
};

// Create a new hashtable which is at least twice as large as the current size.
// Actually, rehashing can make the table smaller (if entries have been removed), but this isn't considered here.
template <typename HashKey, typename HashRecord>
void HashTable<HashKey, HashRecord>::rehash()
{
	vector<HashEntry <HashKey, HashRecord>> oldhashTable = hashTable;

	// Create new double-sized, empty table
	hashTable.resize(nextPrime(2 * oldhashTable.size()));
	for (auto & entry : hashTable)
		entry.info = EMPTY;

	// Copy table over
	activeElements = 0;
	for (auto & entry : oldhashTable)
		if (entry.info == ACTIVE)
			insert(entry.key, entry.rec);

};

// Return true if given entry is active.
template <typename HashKey, typename HashRecord>
bool HashTable<HashKey, HashRecord>::isActive(int currentPos) const
{
	return hashTable[currentPos].info == ACTIVE;
};

//========================//
//ACTUAL HASHING FUNCTIONS//
//=============================================================================================================================
//---------------------
//for finding first pos
//---------------------
template<typename HashKey, typename HashRecord>
size_t HashTable<HashKey, HashRecord>::customHash1(const HashKey & x) const
{
	unsigned int hashKeyVal1 = 0;
	for (int i = 0; i < x.length(); i++)
	{
		(hashKeyVal1 << 7) ^ x[i] ^ hashKeyVal1;	//the actual hash operation
	}
	return (hashKeyVal1 % hashTable.size());	//returning the modified hashKeyVal1 mod the size of the table
};
//----------------------
//for finding second pos
//----------------------
template<typename HashKey, typename HashRecord>
size_t HashTable<HashKey, HashRecord>::customHash2(const HashKey & x) const
{
	unsigned int hashKeyVal2 = 0;
	for (int i = 0; i < x.length(); i++)
	{
		hashKeyVal2 = 29 * hashKeyVal2 + x[i]; 
	}
	unsigned int returnHashKeyVal2 = 44497 - (hashKeyVal2 % 44497);
	return returnHashKeyVal2;
}
//=============================================================================================================================
//						  //
//========================//

// Use lazy deletion to remove an element
// Return boolean to indicate success of operation
template <typename HashKey, typename HashRecord>
bool HashTable<HashKey, HashRecord>::remove(const HashKey & x)
{
	int currentPos = findPos(x);
	if (!isActive(currentPos))
		return false;

	hashTable[currentPos].info = DELETED;
	return true;
};

// Insert item with key x and record pointer h into the hash table.
template<typename HashKey, typename HashRecord>
HashRecord * HashTable<HashKey, HashRecord>::insert(const HashKey x, HashRecord * h)
{
	// Insert x as active
	int currentPos = findPos(x);
	if (isActive(currentPos))
		return NULL;

	hashTable[currentPos].key = x;
	hashTable[currentPos].rec = h;
	hashTable[currentPos].info = ACTIVE;

	// Rehash; see Section 5.5
	if (++activeElements > (int)(hashTable.size() / 2))
		rehash();

	return h;
};

// Return record for item with key x.
template<typename HashKey, typename HashRecord>
HashRecord * HashTable<HashKey, HashRecord>::find(const HashKey & x) const
{
	int pos = findPos(x);
	if (isActive(pos))
		return hashTable[pos].rec;
	return NULL;
};
#endif