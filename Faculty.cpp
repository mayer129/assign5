#include "Faculty.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <iostream>

Faculty::Faculty()
{

}

Faculty::Faculty(int fID)
{
  this->fID = fID;
}

Faculty::Faculty(string name, string level, string department, int fID)
{
  this->name = name;
  this->level = level;
  this->department = department;
  this->fID = fID;
  sIDList = new vector<int>;
}

Faculty::~Faculty()
{
  //delete sIDList;
}

bool operator<(const Faculty &f1, const Faculty &f2)
{
  return f1.fID < f2.fID;
}

bool operator>(const Faculty &f1, const Faculty &f2)
{
  return f1.fID > f2.fID;
}

bool operator==(const Faculty &f1, const Faculty &f2)
{
  return f1.fID == f2.fID;
}

bool operator!=(const Faculty &f1, const Faculty &f2)
{
  return f1.fID != f2.fID;
}

ostream& operator<<(ostream& os, const Faculty &f1)
{
  std::stringstream result;
  std::copy(f1.sIDList->begin(), f1.sIDList->end(), std::ostream_iterator<int>(result, " "));
  
  /*if (!f1.sIDList->isEmpty())
    list = f1.sIDList->returnList();*/

  os <<
    "Name: " << f1.name <<
    "\nLevel: " << f1.level <<
    "\nDepartment: " << f1.department <<
    "\nFaculty ID: " << f1.fID <<
    "\nAdvisees' IDs: " << result.str() <<
    "\n";

  return os;
}
