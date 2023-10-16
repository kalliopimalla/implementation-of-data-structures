#include "SortedArray.h"
#include <iostream>
#include <string.h>
using namespace std;

/*SortedArray::SortedArray()
{
    //ctor
}

SortedArray::~SortedArray()
{
    //dtor
}*/

string SortedArray::getClass()
{
	return "Sorted Array";
}

void SortedArray::insert(string str)// Inserts a pair in the array alphabetically
{
    int pos = 0;
    if (items == 0)
    {
    pairs[pos] = str;
    count[pos]++;
    items++;
    }
    else
    {
        if (searchForInsertion(str, pos)) // If word was found
        {
            count[pos]++; // We increment the count by one
        }
        else // If word is not found
        {
            if(items>maxSize - 5)
            {
                reallocate(2*items);
            }
            for (int i = items++; i>=pos; i--) // Move the items which are right to where our str will be inserted
            {
                pairs[i + 1] = pairs[i]; // One position to the right
                count[i + 1] = count[i]; // Do the same for their count
            }
            pairs[pos] = str; // Str is saved to its postion
            count[pos] = 1;
        }
    }
}

int SortedArray::search(string target) const
{
    int L, R, pos;
    L = 0; // 'left' points to the first index of the array
    R = items; // 'right' points to the last index of the array
    while (L <= R) // While 'left' has 'right' to its right
    {
        pos = (L + R) / 2; // Pos is at half of the two
        if (pairs[pos].compare(target) < 0)
        {
            L = pos + 1; // Move 'left' to the right
        }
        else if (pairs[pos].compare(target) > 0)
        {
            R = pos - 1; // Move 'right' to the left
        }
        else // If target is found
        {
            return count[pos]; // Return count (times in array)
        }
    }
    return 0; // Item is not found, so we return 0 (0 times in array)
}

bool SortedArray::searchForInsertion(string target, int &pos) const  // Finds the position a string should be inserted using binary search. If it doesn't exist it returns false
{
    int L, R;
    L = 0;
    R = items;
    while (L <= R)
    {
        pos = (L + R) / 2;
        if (pairs[pos].compare(target) < 0)
        {
            L = pos + 1;
        }
        else if (pairs[pos].compare(target) > 0)
        {
            R = pos - 1;
        }
        else
        {
            return true; // Word is already in array
        }
    }
    if(pairs[pos].compare(target) < 0)
    {
        pos++;
    }
    if(pos > items)
    {
        pos = items;
    }
    return false; // Word is not yet in array so some other function must insert it alphabetically
}

void SortedArray::print(int n) const  // Print the first n word of the array with their counts
{
    for (int i = 0;i < n;i++)
    {
        cout << pairs[i] << " -> " << count[i] << endl;
    }
	cout << endl;
}

//operators
ostream &operator<<(ostream &o, const SortedArray &a)
{
    o << "SortedArray with " << a.getSize() <<" unique words";
    return o;

}

