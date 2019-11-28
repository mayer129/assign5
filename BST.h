#include <cstddef>
#include <iostream>
#include <fstream>
#include "TreeNode.h"
using namespace std;

template <class T>
class BST
{
private:
  TreeNode<T>* root;

public:
  BST();
  ~BST();

  TreeNode<T>* search(T value);
  void insert(T value);

  bool deleteNode(T value);
  TreeNode<T>* getSuccessor(TreeNode<T>* d);

  bool isEmpty();
  TreeNode<T>* getMin();
  TreeNode<T>* getMax();
  void printTree();
  void recPrint(TreeNode<T>* node);
  void recDest(TreeNode<T>* node);

  void serialize(ofstream& myFile);
  void recSerialize(TreeNode<T>* node, ofstream& myFile);
};

template <class T>
BST<T>::BST()
{
  root = NULL; //empty tree
}

template <class T>
BST<T>::~BST()
{
  recDest(root);
}

template <class T>
void BST<T>::recDest(TreeNode<T>* node)
{
  if (node)
  {
    recDest(node->left);
    recDest(node->right);
    delete node;
  }
}

template <class T>
void BST<T>::recPrint(TreeNode<T>* node)
{
  if (node == NULL)
    return;
//Inorder
  recPrint(node->left);
  cout << node->key << endl;
  recPrint(node->right);
}

template <class T>
void BST<T>::printTree()
{
  recPrint(root);
}

template <class T>
TreeNode<T>* BST<T>::getMin()
{
  TreeNode<T>* current = root;

  if (root == NULL) //empty tree
    return NULL;

  while (current->left != NULL)
    current = current->left;

  return current; //aka return &(current->key)
}

template <class T>
TreeNode<T>* BST<T>::getMax()
{
  TreeNode<T>* current = root;

  if (root == NULL) //empty tree
    return NULL;

  while (current->right != NULL)
    current = current->right;

  return current; //aka return &(current->key)
}

template <class T>
void BST<T>::insert(T value)
{
  TreeNode<T>* node = new TreeNode<T>(value);

  if (root == NULL) //empty tree
    root = node;
  else //tree not empty
  {
    TreeNode<T>* current = root;
    TreeNode<T>* parent = NULL;

    while (true)
    {
      parent = current;

      if (value < current->key)
      {
        current = current->left;
        if (current == NULL) //found left insertion
        {
          parent->left = node;
          break;
        }
      }
      else
      {
        current = current->right;

        if (current == NULL) //found right insertion
        {
          parent->right = node;
          break;
        }
      }
    }
  }
}

template <class T>
TreeNode<T>* BST<T>::search(T value)
{
  if (root == NULL) //empty tree
    return NULL;
   //tree not empty
  TreeNode<T>* current = root;

  while (current->key != value)
  {
    if (value < current->key)
      current = current->left;
    else
      current = current->right;

    if (current == NULL)
      return NULL;
  }

  return current;
}

template <class T>
bool BST<T>::deleteNode(T value)
{
  if (root == NULL) //empty tree
    return false;

  TreeNode<T>* current = root;
  TreeNode<T>* parent = root;
  bool isLeft = true;

  while (current->key != value)
  {
    parent = current;

    if (value < current->key)
    {
      isLeft = true;
      current = current->left;
    }
    else
    {
      isLeft = false;
      current = current->right;
    }

    if (current == NULL) //value does not exist in tree
      return false;
  }
  //found
  if (current->left == NULL && current->right == NULL)
  {
    if (current == root)
      root = NULL;
    else if (isLeft)
      parent->left = NULL;
    else
      parent->right = NULL;
  }
  else
  {
    TreeNode<T>* successor = getSuccessor(current);

    if (current == root)
      root = successor;
    else if (isLeft)
      parent->left = successor;
    else
      parent->right = successor;

    successor->left = current->left;
  }
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d)
{
  TreeNode<T>* current = d->right;
  TreeNode<T>* sp = d;
  TreeNode<T>* successor = d;

  while (current != NULL)
  {
    //traverse tree until we find the successor
    sp = successor;
    successor = current;
    current = current->left;
  }
  //pointers should be correct
  if (successor != d->right)
    sp->left = successor->right;

  return successor;
}

template <class T>
void BST<T>::serialize(ofstream& myFile)
{
  recSerialize(root, myFile);
}

template <class T>
void BST<T>::recSerialize(TreeNode<T>* node, ofstream& myFile)
{
  if (node == NULL)
    return;
  recSerialize(node->left, myFile);
  myFile << node->key << endl;
  recSerialize(node->right, myFile);
}
