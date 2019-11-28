#include <string>
#include <iostream>

using namespace std;

class Student
{
public:
  Student();
  Student(int sID);
  Student(string name, string year, string major, double gpa, int sID, int fID);
  ~Student();

  string name;
  string year;
  string major;

  double gpa;

  int sID;
  int fID;
};

bool operator<(const Student &s1, const Student &s2);
bool operator>(const Student &s1, const Student &s2);
bool operator==(const Student &s1, const Student &s2);
bool operator!=(const Student &s1, const Student &s2);
ostream& operator<<(ostream& os, const Student &s1);
