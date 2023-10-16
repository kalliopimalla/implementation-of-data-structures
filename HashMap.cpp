#include <iostream>
#include <cmath> // For pow function in hash function
#include <string.h>
#include "HashMap.h"

using namespace std;

HashMap::HashMap()
{
	items = 0;
	size = 1000;
	hashmap = new string[size];
	times = new int[size];

	for(int i=0;i<size;i++) // Set all positions in hashmap to "." and times to 0
	{
		hashmap[i] = ".";
		times[i] = 0;
	}
}

HashMap::~HashMap()
{
	delete[] hashmap;
	delete[] times;
}

int HashMap::getSize() const // Return the size of the array
{
	return size;
}

int HashMap::getComparisons() // Returns the total number of comparisons
{
  return comparisons_counter;
}

void HashMap::resize() // Doubles the array
{
	int old_size = size;
	size = size*2;
	string *hash_temp;
	int *times_temp;
	hash_temp = new string[old_size];
	times_temp = new int[old_size];
	int pos;

	for(int i=0;i<old_size;i++) // Create temporaries arrays copying the current state of hashmap
	{
		hash_temp[i] = hashmap[i];
		times_temp[i] = times[i];
	}

	delete[] hashmap;
	delete[] times;
	items = 0;

	hashmap = new string[size]; // Allocate double the memory for the hashmap
	times = new int[size]; // Allocate double the memory for the times array

	for(int i=0;i<size;i++) // Set all positions in hashmap to "." and times to 0
	{
		hashmap[i] = ".";
		times[i] = 0;
	}

	for(int i=0;i<old_size;i++) // Add all the pairs from the temporary arrays
	{
		if(hash_temp[i]!= ".")
		{
			pos = insert(hash_temp[i]); // Saves the position the pair was inserted to change the times its been inserted
			times[pos] += (times_temp[i] - 1) ; // Inserts function makes times 1 since they all appear one times in hash_temp
			// and adds previous times - 1 to compensate for that
		}
	}
}

int HashMap::insert(string str) // Inserts a pair in a position thats given by a hash function
{
  const int M = 1e9 + 7;
	int pos;
	char inserted=0;

	if(items == (3 * size /5 )) // When items are 3/5 of size double the array
	{
		resize();
		insert(str);
		return 0;
	}
	else
	{
	  pos = (hash<string>{}(str) % M) % size;

		while(hashmap[pos] != "." && !inserted) // While pos isn't empty go to pos++. Go to 0 if we are beyond the array
		{
			comparisons_counter++; // Adds in every time there is a string in position we want to insert

			if(hashmap[pos] == str)
			{
				times[pos]++;
				inserted = 1;
			}
			pos ++;
			if(pos == size) // If beyond the array
				pos = 0;
		}
		if(!inserted) // If the string hasn't been inserted during the previous while
		{
			hashmap[pos] = str; // Insert str in first empty position
			times[pos]++;
			items++; // Added a new item
		}
		return pos;
	}
}

int HashMap::search(string str)
{
	const int M = 1e9 + 7;
	int pos;
	pos = (hash<string>{}(str) % M) % size;

	while(hashmap[pos] != ".") // While position is not empty check if the string matches the pair
	{
		if(hashmap[pos] == str)
			return times[pos]; // If str matches pair in pos return times shown from times array

		pos++; // If string wasn't found go to the next position
		if(pos == size) // If next position is out of bounds go to the start
			pos = 0;
	}
	return 0; // If we found the first empty space and haven't found str, str doesn't exist in the hashmap
}

void HashMap::print() // Prints the hashmap linearly
{
	for(int i=0;i<size;i++)
	{
		if(hashmap[i]!= ".") // Print only non empty positions
			cout << hashmap[i] << " -> " << times[i] << endl;
	}
	cout << endl;
}

string HashMap::getClass() // Returns the name of the class
{
	return "Hash Map";
}

//operators
ostream &operator<<(ostream &o, const HashMap &a)
{
    o << "Hash Table with " << a.getSize() <<" unique words";
    return o;

}
