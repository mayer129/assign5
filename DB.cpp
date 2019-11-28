#include "DB.h"

using namespace std;

DB::DB()
{
  stu = new BST<Student>;
  fac = new BST<Faculty>;
  stack = new GenStack<Person>;
}

DB::~DB()
{
  delete stu;
  delete fac;
  delete stack;
}

void DB::deserialize()
{
  ifstream fileStu;
  ifstream fileFac;
  fileStu.open("student.txt");
  fileFac.open("faculty.txt");

  string line = "";
  if (fileStu.is_open() && fileStu.good())
  {
    while (!fileStu.eof())
    {
      string n = "", y = "", m = "";
      double g = 0;
      int sI = 0, fI = 0;

      getline(fileStu, line); //read name
      if (line.empty())
        continue;
      line.erase(0, 6);
      n = line;

      getline(fileStu, line); //read year
      line.erase(0, 6);
      y = line;

      getline(fileStu, line); //read major
      line.erase(0, 7);
      m = line;

      getline(fileStu, line); //read gpa
      line.erase(0, 5);
      g = stod(line);

      line = "";
      getline(fileStu, line); //read sID
      line.erase(0, 12);
      sI = stoi(line);

      getline(fileStu, line); //read fID
      line.erase(0, 12);
      fI = stoi(line);

      Student s(n, y, m, g, sI, fI);
      stu->insert(s);
    }
  }

  if (fileFac.is_open() && fileFac.good())
  {
    while (!fileFac.eof())
    {
      string n = "", l = "", d = "";
      int fI = 0;
      getline(fileFac, line); //read name
      if (line.empty())
        continue;
      line.erase(0, 6);
      n = line;

      getline(fileFac, line); //read level
      line.erase(0, 7);
      l = line;

      getline(fileFac, line); //read department
      line.erase(0, 12);
      d = line;

      getline(fileFac, line); //read fID
      line.erase(0, 12);
      fI = stod(line);

      Faculty f(n, l, d, fI);

      getline(fileFac, line); //read sIDs
      line.erase(0, 15);
      if (line.empty())
      {
        fac->insert(f);
        continue;
      }
        
      //f.sIDList->push_back = stoi(line);
      stringstream iss(line);
      while (iss >> line)
        f.sIDList->push_back(stoi(line));
      fac->insert(f);   
    }
  }

  fileStu.close();
  fileFac.close();
}



void DB::prompt()
{
  while (true)
  {
    string input = "";
    string val1 = "";
    string val2 = "";
    cout <<
      "\nPlease choose an option (1-14):"
      "\n1. Print all students and their information" <<
      "\n2. Print all faculty and their information" <<
      "\n3. Find and display student information given student ID" <<
      "\n4. Find and display faculty information given faculty ID" <<
      "\n5. Given student ID, print name and info of faculty advisor" <<
      "\n6. Given faculty ID, print names and info of all their advisees" <<
      "\n7. Add a new student" <<
      "\n8. Delete a student given student ID" <<
      "\n9. Add a new faculty member" <<
      "\n10. Delete a faculty member given faculty ID" <<
      "\n11. Change student's advisor given student ID and new faculty member ID" <<
      "\n12. Remove advisee from faculty member given faculty member ID and student ID" <<
      "\n13. Rollback" <<
      "\n14. Save & Exit" <<
      "\n";

    cin >> input;

    switch (stoi(input))
    {

      case 1: //print students
      {
        stu->printTree();
        break;
      }

      case 2: //print faculty
      {
        fac->printTree();
        break;
      }

      case 3: //find student using ID
      {
        cout << "Please enter student ID:" << endl; //take student ID
        cin >> val1;
        if (stu->search(stoi(val1))) //if student found
          cout << stu->search(stoi(val1))->key << endl; //print student data
        else //if student not found
          cout << "Error: Student could not be found" << endl;
        break;
      }

      case 4: //find faculty using ID
      {
        cout << "Please enter faculty ID:" << endl; //take faculty member ID
        cin >> val1;
        if (fac->search(stoi(val1))) //if faculty member found
          cout << fac->search(stoi(val1))->key << endl; //print faculty member data
        else //if faculty member not found
          cout << "Error: Faculty member could not be found" << endl;
        break;
      }

      case 5: //find faculty using student ID
      {
        cout << "Please enter student ID:" << endl; //take student ID
        cin >> val1;
        int temp = stoi(val1);
        if (stu->search(temp)) //if student found
        {
          if (fac->search(stu->search(temp)->key.fID)) //if faculty member found
            cout << (fac->search(stu->search(temp)->key.fID)->key) << endl; //print faculty member data
          else //if faculty member not found
            cout << "Error: Faculty member could not be found" << endl;
        }
        else //if student not found
          cout << "Error: Student could not be found" << endl;
        break;

      }

      case 6: //find students using faculty ID
      {
        cout << "Please enter faculty member ID:" << endl;
        cin >> val1;
        if (fac->search(stoi(val1))) //if faculty member found
        {
          vector<int>* vect;
          vect = fac->search(stoi(val1))->key.sIDList; //creates a copy of vector of advisees in faculty member
          for (int i = 0; i < vect->size(); ++i)
          {
            cout << stu->search((*vect)[i])->key << endl; //searches and prints students found in advisee list
          }
        }
        else //if faculty member not found
          cout << "Error: Faculty member could not be found" << endl;
        break;
      }

      case 7: //add student
      {
        string name = "", year = "", major = "";
        double gpa = 0;
        int sID = 0, fID = 0;
        cin.ignore(); //ignore enter from previous input
        //getline allows for multiple words/spaces to be taken in an input. take student data
        cout << "Please enter student name:" << endl;
        getline(cin, name);
        cout << "Please enter student year:" << endl;
        getline(cin, year);
        cout << "Please enter student major:" << endl;
        getline(cin, major);
        cout << "Please enter student gpa:" << endl;
        getline(cin, val1);
        gpa = stod(val1);
        cout << "Please enter student ID:" << endl;
        getline(cin, val1);
        sID = stoi(val1);
        cout << "Student given placeholder faculty advisorless value -1.\nPlease remeber to set the faculty advisor after" << endl;

        if (!stu->search(sID)) //if student does not exists
        {
          stu->insert(Student(name, year, major, gpa, sID, -1)); //insert student with no faculty member
          Faculty f;
          struct Person p = { stu->search(sID)->key, f, true, false, 0 };
          stack->push(p); //add change to stack for rollback
        }
        else //if student already exists
          cout << "Error: Student already exists" << endl;
        break;
      }

      case 8: //delete student using ID
      {
        cout << "Please enter student ID:" << endl; //take student ID
        cin >> val1;
        int temp = stoi(val1);
        if (stu->search(temp)) //if student found
        {
          if (stu->search(temp)->key.fID == -1)
          {
            Faculty f;
            struct Person p = { stu->search(temp)->key, f, true, true, 0 };
            stack->push(p); //add change to stack for rollback
            stu->deleteNode(temp);
          } 
          else
            cout << "Error: Please first remove faculty advisor before deleting" << endl;
        }
        else
          cout << "Error: Student could not be found" << endl;
        break;
      }

      case 9: //add faculty
      {
        string name = "", level = "", department = "";
        int fID = 0;
        cin.ignore(); //ignore enter from previous input
        //getline allows for multiple words/spaces to be taken in an input. take faculty member data
        cout << "Please enter faculty member name:" << endl;
        getline(cin, name);
        cout << "Please enter faculty member level:" << endl;
        getline(cin, level);
        cout << "Please enter faculty member department:" << endl;
        getline(cin, department);
        cout << "Please enter faculty member ID:" << endl;
        getline(cin, val1);
        fID = stoi(val1);
        cout << "Please remember to set the student advisee list after" << endl;
        //cout << "Please enter advisees' IDs seperated by spaces:" << endl;
        //getline(cin, val1);
        Faculty fa(name, level, department, fID);
        //stringstream iss(val1);
        //while (iss >> val1)
          //fa.sIDList->push_back(stoi(val1));
        if (!fac->search(fID)) //if faculty member does not exist
        {
          fac->insert(fa); //insert faculty member with no advisees
          Student s;
          struct Person p = { s, fac->search(fID)->key, false, false, 0 };
          stack->push(p); //add change to stack for rollback
        }
        else //if faculty member already exists
          cout << "Error: Faculty member already exists" << endl;
        /*vector<int>* vect;
        vect = fac->search(fID)->key.sIDList;
        for (int i = 0; i < vect->size(); ++i)
        {
          if (stu->search((*vect)[i])->key.fID == -1)
            stu->search((*vect)[i])->key.fID = fID;
        }*/
        break;
      }

      case 10: //delete faculty using ID
      {
        cout << "Please enter faculty member ID:" << endl;
        cin >> val1;
        int temp = stoi(val1);
        if (fac->search(temp)) //if faculty member found
        {
          if (fac->search(temp)->key.sIDList->empty()) //if faculty advisee list empty
          {
            Student s;
            struct Person p = { s, fac->search(temp)->key, false, true, 0 };
            stack->push(p); //add change to stack for rollback
            fac->deleteNode(temp);
          }
          else //if faculty advisee list not empty
            cout << "Error: Please first remove all student advisees before deleting" << endl;
        }
        else //if faculty member not found
          cout << "Error: Faculty member could not be found" << endl;
        break;
      }

      case 11: //change students advisor using ID and new faculty ID
      {
        cout << "Please enter student ID:" << endl; //take student ID
        cin >> val1;
        cout << "Please enter faculty member ID:" << endl; //take faculty member ID
        cin >> val2;
        int temp1 = stoi(val1);
        int temp2 = stoi(val2);
        if (stu->search(temp1)) //if student found
        {
          if (fac->search(temp2)) //if faculty found
          {
            if (stu->search(stoi(val1))->key.fID == -1) //if student has no advisor
            {
              stu->search(temp1)->key.fID = temp2;
              fac->search(temp2)->key.sIDList->push_back(temp1);
              Faculty f;
              struct Person p = { stu->search(temp1)->key, f, true, false, 1 };
              stack->push(p); //add change to stack for rollback
            }
            else //if student already has advisor
              cout << "Error: Please first reomve faculty advisor before replacing" << endl;
          }
          else //if faculty member not found
            cout << "Error: Faculty member could not be found" << endl;
        }
        else //if student not found
          cout << "Error: Student could not be found" << endl;
        break;
      }

      case 12: //remove student from faculty advisee list using faculty and student ID
      {
        cout << "Please enter faculty member ID:" << endl; //take faculty member ID
        cin >> val1;
        cout << "Please enter student ID:" << endl; //take student ID
        cin >> val2;
        int temp1 = stoi(val2);
        int temp2 = stoi(val1);
        if (fac->search(temp2)) //if faculty member found
        {
          if (stu->search(temp1)) //if student found
          {
            if (stu->search(temp1)->key.fID == stoi(val1)) //if student found on faculty member advisee list
            { //searches vector from begin and end for student ID on list, and removes it. Sets student advisor to default -1 value.
              fac->search(temp2)->key.sIDList->erase(remove(fac->search(temp2)->key.sIDList->begin(), fac->search(temp2)->key.sIDList->end(), temp1), fac->search(temp2)->key.sIDList->end());
              stu->search(temp1)->key.fID = -1;
              struct Person p = { stu->search(temp1)->key, fac->search(temp2)->key, true, false, 2 };
              stack->push(p);
            }
            else //if student not found on faculty member advisee list
              cout << "Error: Student advisee could not be found on given faculty member list" << endl;
          }
          else //if student not found
            cout << "Error: Student could not be found" << endl;
        }
          else //if faculty member not found
            cout << "Error: Faculty member could not be found" << endl;
        break;
      }

      case 13: //rollback bst using stack. //I realize I can just use if(val), but I'm using == true for clarity.
      {
        if (!stack->isEmpty()) //if rollback available
        {
          struct Person p = stack->pop();
          if (p.val == 1) //if case 11: change student advisor
          {
            fac->search(p.s.fID)->key.sIDList->pop_back(); //delete last added student ID from faculty member
            stu->search(p.s.sID)->key.fID = -1; //change student back to advisorless
          }
          else if (p.val == 2) //if case 12: remove student from faculty advisor
          {
            fac->search(p.f.fID)->key.sIDList->push_back(p.s.sID); //add student ID back to faculty member
            stu->search(p.s.sID)->key.fID = p.f.fID; //change student advisor back
          }
          else if (p.del == true) //if delete function, now add
          {
            if (p.isStudent == true) //if student
              stu->insert(p.s); //insert student back in tree
            else
              fac->insert(p.f); //insert faculty member back in tree
          }
          else //if not delete function, now subtract
          {
            if (p.isStudent == true) //if student
              stu->deleteNode(p.s); //insert student back in tree
            else
              fac->deleteNode(p.f); //insert faculty member back in tree
          }
        }
        else //if rollback not available
          cout << "Error: Unable to rollback any further" << endl;
        break;
      }

      case 14: //save & exit program
      {
        ofstream myStu;
        ofstream myFac;
        myStu.open("student.txt");
        myFac.open("faculty.txt");
        if (myStu.is_open())
          stu->serialize(myStu);
        if (myFac.is_open())
          fac->serialize(myFac);
        myStu.close();
        myFac.close();
        return;
      }

      default: //error. runs code again
      {
        cout << "Error: Invalid Input. Please try again" << endl;
      }

    }
  }
}