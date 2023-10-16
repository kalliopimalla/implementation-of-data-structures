#include <iostream>
#include <string.h>
#include <cstdlib>
#include "AVLtree.h"
#include "BinaryTree.h"
using namespace std;


AVLtree::AVLtree() // Constructor
{
  root = NULL;
  size = 0;
}

AVLtree::~AVLtree() // Destructor
{
    DestroyTree(this->root);
}

void AVLtree::DestroyTree(node * T) // Function that destroys the tree from T node and under
{
    if (T) // If node is not NULL
    {
        DestroyTree(T->left); // Go to left child of the node
        DestroyTree(T->right); //  Go to right child of the node
        delete T; // Delete node
    }
}
int AVLtree::getSize()
{
    return size;
}

string AVLtree::getClass()
{
	return "AVL Tree";
}

void AVLtree::insert(string str) // Insert function that matches the template function in function.h
{
    size++;
    this->root = insert(this->root, str);
}

int AVLtree::search(string str) const // search function that matches the template function in function.h
{
    return searchword(this->root, str);
}

AVLtree::node *AVLtree::insert(node * T, string str) // Recursive function that inserts str to the tree
{
  if(T==NULL) // If T is NULL then str doesn't exist in the tree so we insert it in this node
  {
    T = new node;
    T->times = 1;
    T->right = NULL;
    T->left = NULL;
    T->pair = str;
  }
  else if(str.compare(T->pair) > 0) // If str is alphabetically bigger then we go to the right child of the node
  {
    T->right = insert(T->right, str);
    T = balanced(T);
  }
  else if(str.compare(T->pair) < 0) // If str is alphabetically smaller then we go to the left child of the node
  {
    T->left = insert(T->left,str);
    T = balanced(T);
  }
  else if(str.compare(T->pair) == 0 && str.length() == T->pair.length()) // If str already exists in the tree we increment times by 1
  {
      T->times++;
      size--;
  }
  return T;
}

int AVLtree::searchword(node *T,string str) const // Recursive function that searches for a specific word
{
  if(T == NULL) // If node is NULL then str doesn't exist
  {
      return -1;
  }
  else if(str.compare(T->pair) > 0)  // If str is alphabetically bigger then we go to the right child of the node
  {
      return searchword(T->right, str);
  }
  else if(str.compare(T->pair) < 0) // If str is alphabetically smaller then we go to the left child of the node
  {
      return searchword(T->left, str);
  }

  return T->times; // If str exists and we return how many times the word has appeared in our text

}
AVLtree::node *AVLtree::deleteword(node *T,string str) // Recursive function that deletes a function
{

  if(T==NULL) // If T is NULL then the word doesn't exist
    return T;
  if( str.compare(T->pair)<0 )  // If the word is alphabetically bigger then we go to the right child of the node
    T->left=deleteword(T->left,str);
  else if(str.compare(T->pair)>0 ) // If the word is alphabetically smaller then we go to the left child of the node
    T->right=deleteword(T->right,str);
  else // If word is found
  {
    if((T->left==NULL) || (T->right==NULL) ) // If at least on of the childs is NULL
    {
        node *P = T->left; // We create a struct T, equal to T's left child
        if(T) // If T isn't NULL
          P = T->left ; // T is equal to root's left child
        else
          P = T->right; // T is equal to root's right child
        if(T == NULL) // If T is NULL
        {
          P = T; // Then will be equal to root
          T = NULL; // And root will be equal to NULL
        }
       else
       {
           *T=*P;
       }
       free(P);
    }
    else // If none of the root's childs is NULL
    {
      node* P= min(T->right); // T is equal to the smallest node of root's children
      T->pair=P->pair; // Root's word is equal to T's word
      T->right=deleteword(T->right,P->pair); // The right child of root will become equal to the return value of delete word with the right child of root and the word in T
    }
  }
  if (T==NULL)
    return T;
  T=balanced(T); // We call the fun that balances our tree
  return T;
}

AVLtree::node *AVLtree::min(node *start)
{
   node* MIN=start;
  while(MIN->left!=NULL) // While the left child of MIN is NOT null
      MIN=MIN->left; // MIN is equal to its left child
  return MIN;
}

unsigned long long int AVLtree::height(node* T)
{
  int h=0;
  int lh=0;
  int rh=0;
  int max;
  if(T!=NULL) // If T is not NULL we count the heights of its left and right children and keep the biggest
  {
    rh=height(T->right);
    lh=height(T->left);
    if(lh>rh)
      h=lh+1;
    else
      h=rh+1;
  }
  return h;

}
int AVLtree::difference(node *T) // Returns the difference of the children of T node
{
  int rh;
  int lh;
  int difference;

  rh=height(T->right);
  lh=height(T->left);
  difference=lh-rh;
  return difference;
}
AVLtree::node *AVLtree::balanced(node *T)
{
  int balance;
  balance=difference(T);
  if(balance>1) // If the difference of right and left subtree is bigger than 1, the height of the left subtree is bigger than that of the right by more than 1
  {
    if(difference(T->left)>0) // If the left subtree is not balanced
      T=leftleft(T); // Then we do a left-left rotation
    else // If it is balanced
      T=leftright(T); // We do a left-right rotation
  }
  else if(balance<-1) // If the difference of right and left subtree is smaller than -1, the height of the right subtree is bigger than that of the left by more than 1
  {
    if(difference(T->right)>0) // If right subtree isn't balanced
       T=rightleft(T); // We do a right-left rotation
     else // If it is balanced
      T=rightright(T); // We do a right-right rotation
  }
  return T;
}
AVLtree::node *AVLtree::rightright(node *T) // Function that makes a simple right rotation
{
  node *t;
  t=T->right;
  T->right=t->left;
  t->left=T;
  return t;
}
AVLtree::node *AVLtree::leftleft(node *T) // Function that makes a simple left rotation
{
  node *t;
  t=T->left;
  T->left= t->right;
  t->right=T;
  return t;
}
AVLtree::node *AVLtree::leftright(node *T) // Function that makes a left-right rotation
{
  node *t;
  t=T->left;
  T->left=rightright(t);
  return leftleft(T);
}
AVLtree::node *AVLtree::rightleft(node *T)// Function that makes a right-left rotation
{
  node *t;
  t=T->right;
  T->right=leftleft(t);
  return rightright(T);
}


void AVLtree::inorder(node *T)
{
  if(T==NULL)
    return;
  inorder(T->left);
  cout<<T->pair<< " ";
  inorder(T->right);
}

void AVLtree::preorder(node *T)
{
  if(T==NULL)
    return;
  cout<<T->pair << " ";
  preorder(T->left);
  preorder(T->right);
}

void AVLtree::postorder(node *T)
{
  if(T==NULL)
    return;
  postorder(T->left);
  postorder(T->right);
  cout<<T->pair<< " ";
}

void AVLtree::inorder()
{
    inorder(this->root);
}

void AVLtree::preorder()
{
    preorder(this->root);
}

void AVLtree::postorder()
{
    postorder(this->root);
}

ostream &operator<<(ostream &o, AVLtree &a)
{
    o << "AVL tree with " << a.getSize() <<" unique words";
    return o;

}
