#include <cstddef>
#include <iostream>
using namespace std;

template <class T>
class TreeNode
{
public:
  TreeNode();
  TreeNode(T k);
  ~TreeNode();

  T key;
  TreeNode* left;
  TreeNode* right;
};

template <class T>
TreeNode<T>::TreeNode()
{
  cout << "emptynode" << endl;
  key = NULL;
  left = NULL;
  right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T k)
{
  key = k;
  left = NULL;
  right = NULL;
}

template <class T>
TreeNode<T>::~TreeNode()
{
  left = NULL;
  right = NULL;
}
