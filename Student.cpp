#include "Student.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

void Student::Print() {
    std::cout << "ID: " << this->studentID << std::endl;
    std::cout << "Name: " << this->fullName << std::endl;
    std::cout << "Grade: " << this->grade << std::endl;
    std::cout << "Major: " << this->major << std::endl;
    std::cout << "GPA: " << this->gpa << std::endl;
    std::cout << "Advisor ID: " << this->advisorID << std::endl;
    std::cout << std::endl;
}

std::string Student::ToString() {
    std::string studentInfo;

    // Convert double val, gpa, to string at 2 decimal places
    std::ostringstream stringGPA;
    stringGPA << gpa;
    stringGPA << std::setprecision(2);

    // Convert student info to a single line to input onto an output file
    studentInfo = std::to_string(studentID) + ",";
    studentInfo += fullName + ",";
    studentInfo += grade + ",";
    studentInfo += major + ",";
    studentInfo += stringGPA.str() + ",";
    studentInfo += std::to_string(advisorID);

    return studentInfo;
}

std::ostream& operator<<(std::ostream& out, Student& student) {
    out << student.ToString();
    return out;
}

std::istream& operator>>(std::istream& in, Student& student) {

  std::string line;
  std::string inputName;
  std::string inputGrade;
  std::string inputMajor;
  double inputGpa;
  int inputAdvisorID;
  int inputStudentID;
  char delim;

  in >> inputStudentID >> delim;
  getline(in,inputName, ',');
  getline(in, inputGrade, ',');
  getline(in, inputMajor, ',');
  in >> inputGpa >> delim;
  in >> inputAdvisorID;
  getline(in, line);

  student.SetStudentID(inputStudentID);
  student.SetFullName(inputName);
  student.SetGrade(inputGrade);
  student.SetMajor(inputMajor);
  student.SetGPA(inputGpa);
  student.SetAdvisorID(inputAdvisorID);

  return in;
}
