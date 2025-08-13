#include "Faculty.h"
#include <iostream>
#include <fstream>
using namespace std;


void Faculty::AddStudentToList(int StudentID){
  studentList.push_back(StudentID);
}

void Faculty::RemoveStudentFromtList(int studentID) {

  // Iterate through list then remove student
  for (int i = 0; i < studentList.size(); i++) {
    if (studentList[i] == studentID) {
      studentList.erase(studentList.begin() + i);
      std::cout << "Successfully removed student" << std::endl;
      break;
    }
  }
}

bool Faculty::HasStudent(int studentID){

  // Iterate through list to find if ID exists
  for (int i = 0; i < studentList.size(); i++) {
    if (studentList[i] == studentID)
      return true;
  }
  return false;
}

void Faculty::PrintStudentList(){

  if (studentList.size() == 0) {
    std::cout << "No Advisees";
  } else {
    std::cout << "List of Advisees:" << std::endl;
    for(int i = 0; i < studentList.size(); i++) {
      cout << studentList.at(i);
      if (i == studentList.size() - 1) { // Avoid adding a ', ' at the end of the list
        continue;
      } else {
        cout << ", ";
      }
    }
  }
  std::cout << std::endl;

}

int Faculty::GetStudentListSize(){
  return studentList.size();
}

void Faculty::Print() {

  std::cout << "ID: " << facultyID << std::endl;
  std::cout << "Name: " << name << std::endl;
  std::cout << "Level: " << level << std::endl;
  std::cout << "Department: " << department << std::endl;
  PrintStudentList();
  std::cout << std::endl;
}

std::string Faculty::ToString() {

  completeInfo = std::to_string(facultyID) + ",";
  completeInfo += name + ",";
  completeInfo += level + ",";
  completeInfo += department + ",";

  for (int i = 0; i < studentList.size(); i++) {
    completeInfo += std::to_string(studentList.at(i));
    if (i+1 != studentList.size()) {
      completeInfo += ",";
    }
  }
  //completeInfo += '\n';
  return completeInfo;
}

std::ostream& operator<<(std::ostream& out, Faculty& faculty) {
  out << faculty.ToString();
  return out;
}

std::istream& operator>>(std::istream& in, Faculty& faculty) {

  vector<int> inputList;
  std::string inputName;
  std::string  inputLevel;
  std::string inputDepartment;
  std::string line;
  int inputAdvisee;
  int inputFacultyID;
  char delim;

  in >> inputFacultyID >> delim;
  getline(in,inputName, ',');
  getline(in, inputLevel, ',');
  getline(in,inputDepartment, ',');

  // Read till end of line, and extract the advisee id's
  getline(in, line);
  std::stringstream ss(line);
  while (!ss.eof() && line != "") {
    ss >> inputAdvisee >> delim;
    if (inputAdvisee) {
      faculty.AddStudentToList(inputAdvisee);
    }
  }


  faculty.SetFacultyID(inputFacultyID);
  faculty.SetName(inputName);
  faculty.SetLevel(inputLevel);
  faculty.SetDepartment(inputDepartment);

  return in;
}
