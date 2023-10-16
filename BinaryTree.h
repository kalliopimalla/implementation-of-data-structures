#ifndef BINARYTREE_h
#define BINARYTREE_h
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class BinaryTree
{
  public:
    struct node;
	  BinaryTree(); // Constructor
	  ~BinaryTree(); // Destructor

		void DestroyTree(node *T); // Destroys the tree under a given node

	  int getSize(); // Size getter
		virtual string getClass(); // Returns the name of the class

		node *insert(string str, node *T); // Inserts a string in the tree
		int search(string str, node *T); // Searches for a pair in the tree (return times)

		void inorder(node *T); // Prints tree from T node under

		virtual void insert(string str); // Easier call for main. Calls insert with root
		int search(string str); // Easier call for main. Calls search with root
		void inorder(); // Easier call for main. Calls inorder with root

  private:
    struct node
	  {
	    string pair; // The pair
	    int times; // Times a pair has been inserted
	    node *left; // Left child
	    node *right; // Right child
		}* root; // Tree root creation
    int size; // Number of unique pairs that have been inserted
};
#endif
