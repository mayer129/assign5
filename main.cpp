#include "DB.h"
#include <iostream>
#include <fstream>
#include <cstddef>

using namespace std;

int main (int argc, char** argv)
{

/*
  BST<int> tree;
  tree.insert(10);
  tree.insert(9);
  tree.insert(16);
  tree.insert(24);
  tree.insert(14);
  tree.deleteNode(16);
  tree.deleteNode(299);
  tree.printTree();

  Faculty f("Jack D", "Professor", "Engineering", 123456);

  //cout << f << endl;

  Faculty c("Jack C", "AssistantProfessor", "Math", 123455);


  //BST<Faculty> *tem = new BST<Faculty>;
  BST<Faculty> t;
  cout << "here" << endl;
  t.insert(Faculty("Jack D", "Professor", "Engineering", 123456));
  cout << "here2" << endl;
  t.insert(c);
  cout << "here3" << endl;
  t.printTree();

  cout << "herelol" << endl;
  Faculty c0 = t.search(123456)->key;
  cout << c0.name << endl;
  cout << t.search(123456)->key << endl;

  if (t.search(123455))
    cout << t.search(123455)->key << endl;
  else
    cout << "Student could not be found" << endl;
*/

  DB databs;
  databs.deserialize();
  databs.prompt();


  //delete tem;

  return 0;
}
