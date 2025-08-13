#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <sstream>
#include <vector>

class Faculty{
private:
  int facultyID;
  std::string name;
  std::string level;
  std::string department;
  std::string completeInfo;

public:
  Faculty() {
    this->facultyID = -1;
    this->name = "";
    this->level = "";
    this->department = "";
  }

  Faculty(int facultyID, std::string name, std::string level, std::string department) {
    this->facultyID = facultyID;
    this->name = name;
    this->level = level;
    this->department = department;
  }

  ~Faculty() { };

  std::vector<int> studentList;

  void SetFacultyID(int facultyID) { this->facultyID = facultyID; }
  void SetName(std::string name) { this->name = name; }
  void SetLevel(std::string level) { this->level = level; }
  void SetDepartment(std::string department) { this->department = department; }

  int GetFacultyID() { return this->facultyID; }
  std::string GetName() { return this->name; }
  std::string GetLevel() { return this->level; }
  std::string GetDepartment() { return this->department; }

  void PrintStudentList();
  void AddStudentToList(int studentID);
  void RemoveStudentFromtList(int studentID);
  bool HasStudent(int studentID);
  int GetStudentListSize();
  int StudentListAt(int i);
  
  void Print();
  std::string ToString();

  bool operator==(Faculty rhs) { return (this->facultyID == rhs.facultyID); }
  bool operator<(Faculty rhs) { return (this->facultyID < rhs.facultyID); }
  bool operator>(Faculty rhs) { return(this->facultyID > rhs.facultyID); }

  friend std::ostream& operator<<(std::ostream& out, Faculty& faculty);
  friend std::istream& operator>>(std::istream& in, Faculty& faculty);

};

#endif