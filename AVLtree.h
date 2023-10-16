#ifndef AVTREE_h
#define AVLTREE_h

#include <iostream>
#include <string.h>
using namespace std;
#include "BinaryTree.h"

class AVLtree:public BinaryTree
{
	public:
		struct node;

		AVLtree(); // Constructor
		~AVLtree(); // Destructor
		void DestroyTree(node *T);  // Destroys the tree from T and under
		int getSize(); // Size getter
		virtual string getClass(); // Returns the name of the class

    node *insert(node *T, string str); // Inserts a string in the tree
    int searchword(node *, string str) const; // Searches for a string
    node *deleteword(node *, string str);  // Deletes a string from the tree (if it exists)


		node *min(node *start); // Finds the alphabetically smallest word
		unsigned long long int height(node *T); // Calculates the height of the tree
		int difference(node *T); // Calculates the difference between the right and left subtree
		node *balanced(node *T); // Balances the tree
		node *rightright(node *T); // Function that makes a right-right rotation
		node *leftleft(node *T); // Function that makes a left-left rotation
		node *leftright(node *T); // Function that makes a left-right rotation
		node *rightleft(node *T); // Function that makes a right-left rotation
		void inorder(node *T); // Prints nodes in inorder and works recursively
		void preorder(node *T);  // Prints nodes in preorder and works recursively
		void postorder(node *T);  // Prints nodes in postorder and works recursively

		// Same functions but easier to call in main (calling them from the root)
		void insert(string);
		int search(string) const;
		void inorder();
		void preorder();
		void postorder();

  private:
    struct node
		{
			string pair; // The pair
			int times;   // How many times the word appears
			node * left; // Left child
			node * right;// Right child
		}* root;// Tree root creation
		int size; // Total unique words our data structure has so far

};

ostream &operator<<(ostream &, const AVLtree &);
#endif
