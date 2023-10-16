#include "UnsortedArray.h"
#include <iostream>
#include <string>
using namespace std;

UnsortedArray::UnsortedArray()
{
  items = 0;
  count = new int[MAX_SIZE];
  pairs = new string[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++)
    {count[i] = 0;
    pairs[i] = '.';}
}

UnsortedArray::~UnsortedArray()
{
  delete [] count;
  delete [] pairs;
}

int UnsortedArray::getSize() const
{return items;}


string *&UnsortedArray::getPairs()
{
	return pairs;
}

string UnsortedArray::getClass()
{
	return "Unsorted Array";
}

void UnsortedArray::print(int n) const  // Print the first n word of the array with their counts
{
    for (int i = 0;i < n;i++)
    {
        cout << pairs[i] << " -> " << count[i] << endl;
    }
	cout << endl;
}

int UnsortedArray::search(string str) const // Performs a basic linear search and returns count
{
    for (int i = 0;i < items;i++)
    {
        if(str == pairs[i]) // If word is found
        {
            return count[i]; // Return count (times appeared)
        }
    }
    return 0; // If word is not found we return 0 (0 appearances in text)
}

int UnsortedArray::searchPos(string str) const // Performs a basic linear search and returns index of word
{
    for (int i = 0;i < items;i++)
    {
        if(str == pairs[i]) // If word is found
        {
            return i;  // Return index
        }
    }
    return -1; // If not found, return -1
}

void UnsortedArray::insert(string str)
{
    if(items == maxSize) // When there is no room for other unique items
    {
        reallocate(2*items); // Double the array size
    }
    int pos = searchPos(str); // Search for word
    if (pos == -1) // If word is not found
    {
        count[items] = 1;
        pairs[items++] = str; // Add new word in the end of the Array
    }
    else // If word is found
    {
        count[pos]++; // we increment the count by one
    }
}

bool UnsortedArray::remove(string str)
{
    int pos = searchPos(str); // Find the pos
    if (pos == -1) // If not found
    {
        return false; // Removing cannot be performed
    }
    for (int i = pos; i < items - 1; i++)  // Move all the words to the left
    {
        pairs[i] = pairs[i + 1];
        count[i] = count[i + 1];
    }
    return true; // Removing was successfull

}

bool UnsortedArray::reallocate(int n)
{
  string *temp;
  int *temp_times;
	temp = new string[items];
  temp_times = new int[items];
	if (temp == NULL || temp_times == NULL)
	   return false;

	for (int i=0;i<items;i++) // Copy stuff from class arrays to temporary ones
  {
      temp[i] = pairs[i];
      temp_times[i] = count[i];
  }

  // Delete old and create bigger arrays
  delete[] pairs;
  delete[] count;

  pairs = new string[n];
  count = new int[n];

  for (int i=0;i<items;i++) // Copy stuff from temp arrays back to class arrays
  {
      pairs[i] = temp[i];
      count[i] = temp_times[i];
  }

  maxSize = n; // maxSize has changed
  return true;
}

//operators
ostream &operator<<(ostream &o, const UnsortedArray &a)
{
    o << "UnsortedArray with " << a.getSize() <<" unique words";
    return o;

}
