#include <iostream>
#include <string.h>
#include "BinaryTree.h"
using namespace std;

BinaryTree::BinaryTree() //constructor
{
    size = 0;
    root = NULL;
}

void BinaryTree::DestroyTree(node *T) //  Function that deletes the tree
{
    if (T) // If node exists
    {
        DestroyTree(T->left); // Destroy the left child
        DestroyTree(T->right); // Destroy the right child
        delete T; // Delete the node
    }
}

BinaryTree::~BinaryTree() // Destructor
{
    DestroyTree(this->root);
}

int BinaryTree::getSize()
{
    return size;
}

string BinaryTree::getClass()
{
	return "Binary Tree";
}

BinaryTree::node *BinaryTree::insert(string str, node *T) // Recursive function that searches where the pair should be based on ASCII value and inserts it at that place
{
	if(T==NULL) // if node doesn't exist insert str into node
	{
		T = new node;
		T->pair = str;
		T->times = 1;
		T->left = NULL;
		T->right = NULL;
		size++;
	}
	else
	{
		int decision = T->pair.compare(str); // Dictates where to go
		if(decision > 0) // Means str is smaller alphabetically than the pair in node
		{
			T->left = insert(str,T->left); // Go insert to the left child
		}
		else if(decision < 0) // Means str is bigger alphabetically than the pair in node
		{
			T->right = insert(str,T->right); // Go insert to the right child
		}
		else if(decision == 0) // The pairs are the same
		{
			T->times++;
		}
	}
	return T;
}

void BinaryTree::insert(string str) // Gives the starting command to insert a string starting from the root
{
	this->root = insert(str, root);
}

int BinaryTree::search(string str, node *T) // Recursive function that searches for a string in the tree
{
	if(T==NULL) // If T doesn't exists it means that str isn't in the path we followed so it isn't in the tree
	{
		return 0;
	}
	else
	{
		int decision = T->pair.compare(str); // Calculates the alphabetical difference of the pair in the node and the string we are searching for
		if(decision == 0) // If they are the same
		{
			return T->times;
		}
		else if (decision > 0) // If the pair is bigger than the str we are searching for, go search left
		{
			return search(str, T->left);
		}
		else if (decision <0) // If the pair is smaller than the str we are searching for, go search right
		{
			return search(str,T->right);
		}
	}
}

int BinaryTree::search(string str)// Easier function to call for main
{
	return search(str,root);
}

void BinaryTree::inorder(node *T) // Prints the tree from T node and under alphabetically using inorder
{
	if (T)
	{
		inorder(T->left);
		cout << T->pair << " -> " << T->times << endl;
		inorder(T->right);
	}
}

void BinaryTree::inorder() // Easier function to call for main
{
	inorder(root);
}
