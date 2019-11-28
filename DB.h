#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include "GenStack.h"
#include <iostream>
#include <fstream>
#include <cstddef>
#include <sstream>
#include <algorithm>


using namespace std;

struct Person
{
  Student s;
  Faculty f;
  bool isStudent;
  bool del;
  int val;
};

class DB
{
public:
  DB();
  ~DB();

  BST<Student>* stu;
  BST<Faculty>* fac;

  GenStack<Person>* stack;

  void deserialize();
  void prompt();
};
