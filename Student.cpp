#include "Student.h"

Student::Student()
{

}

Student::Student(int sID)
{
  this->sID = sID;
}

Student::Student(string name, string year, string major, double gpa, int sID, int fID)
{
  this->name = name;
  this->year = year;
  this->major = major;
  this->gpa = gpa;
  this->sID = sID;
  this->fID = fID;
}

Student::~Student()
{

}

bool operator<(const Student &s1, const Student &s2)
{
  return s1.sID < s2.sID;
}

bool operator>(const Student &s1, const Student &s2)
{
  return s1.sID > s2.sID;
}

bool operator==(const Student &s1, const Student &s2)
{
  return s1.sID == s2.sID;
}

bool operator!=(const Student &s1, const Student &s2)
{
  return s1.sID != s2.sID;
}

ostream& operator<<(ostream& os, const Student &s1)
{
    os << "Name: " << s1.name <<
      "\nYear: " << s1.year <<
      "\nMajor: " << s1.major <<
      "\nGPA: " << s1.gpa <<
      "\nStudent ID: " << s1.sID <<
      "\nAdvisor ID: " << s1.fID <<
      "\n";

  return os;
}
