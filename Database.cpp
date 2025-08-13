/*
File Name: Database.cpp
What it does: This file is essentially responsible for any changes made to the Student or Faculty Database and how those changes are written out to a file.
*/

#include "Database.h"
#include <fstream>

/*
Function Name: AddStudent
What it does: This functions adds a student to the student database.
Parameters and Data types: The only parameter for this function is a pointer to the student object.
Return value and data type: Since this is a void function, no value is returned.
*/
void Database::AddStudent(Student* student){
  studentDB.insert(new TreeNode<Student*>(student->GetStudentID(), student));
}

/*
Function Name: AddFaculty
What it does: This functions adds a faculty member to the student database.
Parameters and Data types: The only parameter for this function is a pointer to the faculty object.
Return value and data type: Since this is a void function, no value is returned.
*/
void Database::AddFaculty(Faculty* faculty){
  facultyDB.insert(new TreeNode<Faculty*>(faculty->GetFacultyID(), faculty));
}

/*
Function Name: AddAdvisee
What it does: This function adds a student advisee to a faculty member's list of advisees. We also maintain referential integrity given
the circumstance that the student had a previous advisor by removing that student from the advisor.
Parameters and Data Types: The parameters for this function are the faculty ID and student ID.
Return value and data type: If either the faculty object or student object is null, the function will return -1. Otherwise, it returns 0.
*/
int Database::AddAdvisee(int facultyID, int studentID) {

  Student* studentTemp = studentDB.find(studentID);
  Faculty* facultyTemp = facultyDB.find(facultyID);

  if (facultyTemp == nullptr) {
    std::cout << "Faculty, " << facultyID << " does not exist." << std::endl;
    return -1;
  } else if (studentTemp == nullptr) {
    std::cout << "Student, " << studentID << " does not exist." << std::endl;
    return -1;
  }

  if(!(facultyTemp->HasStudent(studentID))){
    facultyTemp->AddStudentToList(studentID);
    studentTemp->SetAdvisorID(facultyID);
  }
  return 0;
}

/*
Function Name: AddAdvisor
What it does: This function adds a new advisor to a student by checking to make sure both the student and faculty member
exist and then set the student's advisor ID to that faculty member.
Parameters and Data Types: The parameters are the student ID and faculty ID
Return value and data type: If either the student or faculty member does not exist, return -1. Otherwise, return 0.
*/
int Database::AddAdvisor(int studentID, int newFacultyID){

  Faculty* facultyTemp = facultyDB.find(newFacultyID);
  Student* studentTemp = studentDB.find(studentID);

  if(facultyTemp == nullptr) {
    std::cout << "Faculty, " << newFacultyID << " does not exist." << std::endl;
    return -1;
  }
  if(studentTemp == nullptr) {
    std::cout << "Student, " << studentID << " does not exist." << std::endl;
    return -1;
  }

  studentTemp->SetAdvisorID(newFacultyID);
  return 0;
}

/*
Function Name: RemoveStudent
What it does: This function removes a student from the student database. We maintain referential integrity by removing a student
from a faculty member's list if the faculty member has the student.
Parameters and Data Types: The only parameter is the student ID
Return value and data type: If the student does not exist, return -1. Otherwise, return 0.
*/
int Database::RemoveStudent(int studentID){

  Student* studentTemp = studentDB.find(studentID);

    // Student was not found in database
    if (studentTemp == nullptr) {
      std::cout << "Student does not exist!" << std::endl;
      return -1;
    }

    // There is an advisor to remove this student from their advisee list, referential integrity
    if (studentTemp->GetAdvisorID() != -1) {
      Faculty* facultyTemp = facultyDB.find(studentTemp->GetAdvisorID());
      if(facultyTemp == nullptr){
        std::cout << "Student doesn't have a valid advisor" << std::endl;
      }
      else if(facultyTemp->HasStudent(studentID)) {
        facultyTemp->RemoveStudentFromtList(studentTemp->GetStudentID());
      }
    }

    studentDB.remove(studentID);
    return 0;
}

/*
Function Name: RemoveFaculty
What it does: This function removes a faculty member from the faculty database. We maintain referential integrity by stopping the process
if there are any students still in the faculty member's list of advisees.
Parameters and Data Types: The only parameter is the faculty ID
Return value and data type: If the faculty member does not exist, return -1. Otherwise, return 0.
*/
int Database::RemoveFaculty(int facultyID){

  Faculty* facultyTemp = facultyDB.find(facultyID);

  if (facultyTemp == nullptr) {
    std::cout << "Faculty Member does not exist!" << std::endl;
    return -1;
  }

  // Faculty still has students in their advisee list, they must be re-assigned to a new advisor
  if (facultyTemp->GetStudentListSize() != 0) {
    std::cout << facultyTemp->GetName() << " still has advisee(s) in their list!" << std::endl;
    std::cout << "Re-assign advisors to those students before removing " << facultyTemp->GetName() << std::endl;
    return -1;
  }

  facultyDB.remove(facultyID);
  return 0;
}

/*
Function Name: RemoveAdvisee
What it does: This function removes an advisee from a faculty member's list of advisees given the student ID and faculty ID and sets the student's ID to -1.
Parameters and Data Types: The parameters are the faculty ID and the student ID.
Return value and data type: If the student or faculty member does not exist or the faculy member has no students in it's list of advisees, return -1.
Otherwise, return 0.
*/
int Database::RemoveAdvisee(int facultyID, int studentID){

  Faculty* facultyTemp = facultyDB.find(facultyID);
  if (facultyTemp == nullptr) {
    std::cout << "Faculty, " << facultyID << ", does not exist!" << std::endl;
    return -1;
  }

  if(facultyTemp->HasStudent(studentID)) {

    Student* studentTemp = studentDB.find(studentID);
    if(studentTemp == nullptr) {
      std::cout << "Student, " << studentID << ", does not exist!" << std::endl;
      return -1;

    // Remove advisor from the student
    } else {
      studentTemp->SetAdvisorID(-1);
    }

    facultyTemp->RemoveStudentFromtList(studentID);
    std::cout << "Succesfully removed!" << std::endl;

  } else {
    std::cout << "Faculty member does not have this student!" << std::endl;
    return -1;
  }

  return 0;
}

/*
Function Name: RemoveAdvisor
What it does: This function removes an advisor from a student. We maintain referential integrity by checking if the student has an advisor. If so, remove the student
from the advisor and set the student's ID to -1.
Parameters and Data Types: The only parameter is the student ID.
Return value and data type: If the student does not exist return -1.vOtherwise, return 0.
*/
int Database::RemoveAdvisor(int studentID){

  Student* studentTemp = studentDB.find(studentID);

  // Student was not found in database
  if(studentTemp == nullptr){
    std::cout << "Student, " << studentID << " does not exist." << std::endl;
    return -1;
  }

  if(studentTemp->GetAdvisorID() != -1){
    RemoveAdvisee(studentTemp->GetAdvisorID(), studentID);
  }

  studentTemp->SetAdvisorID(-1);
  return 0;
}

/*
Function Name: ChangeStudentAdvisor
What it does: This function changes the advisor of a student. We maintain referential integrity by removing that the student from the previous list of advisees
of the student's old advisor and add it to the new advisor's list of advisees.
Parameters and Data Types: The parameters are the student ID and the new faculty ID.
Return value and data type: If the student and faculty member does not exist, return -1. Otherwise, return 0.
*/
int Database::ChangeStudentAdvisor(int studentID, int newFacultyID){

  Faculty* facultyTemp = facultyDB.find(newFacultyID);
  Student* studentTemp = studentDB.find(studentID);
  if(facultyTemp == nullptr){
    std::cout << "Faculty, " << newFacultyID << " does not exist." << std::endl;
    return -1;
  }
  else if(studentTemp == nullptr){
    std::cout << "Student, " << studentID << " does not exist." << std::endl;
    return -1;
  }

  if(studentTemp->GetAdvisorID() == -1){ // Case 1: Student does not have an existing advisor
    studentTemp->SetAdvisorID(newFacultyID);
    facultyTemp->AddStudentToList(studentID);
  }
  else{                                 // Case 2: Student has an exisiting advisor
    Faculty* prevAdvisor = facultyDB.find(studentTemp->GetAdvisorID());
    prevAdvisor->RemoveStudentFromtList(studentID);

    if(!(facultyTemp->HasStudent(studentID))){
      facultyTemp->AddStudentToList(studentID);
    }
    studentTemp->SetAdvisorID(newFacultyID);
  }

  return 0;
}


/*
Function Name: FindStudent
What it does: This function finds a student in the student database given their ID and displays their information.
Parameters and Data Types: The only parameter is student ID
Return value and data type: If the student does not exist, return -1. Otherwise, return 0.
*/
int Database::FindStudent(int studentID){

  Student* temp = studentDB.find(studentID);
  if(temp == nullptr){
    std::cout << "Student does not exist! " << std::endl;
    return -1;
  }
  temp->Print();
  //Add Press to Continue and change to Find that Gil made
  return 0;

}

/*
Function Name: FindFaculty
What it does: This function finds a faculty member in the faculty database given their ID and displays their information.
Parameters and Data Types: The only parameter is faculty ID
Return value and data type: If the student does not exist, return -1. Otherwise, return 0.
*/
int Database::FindFaculty(int facultyID){

  Faculty* temp = facultyDB.find(facultyID);
  if (temp == nullptr) {
    std::cout << "Faculty member does not exist! " << std::endl;
    return -1;
  }
  temp->Print();
  temp->PrintStudentList();
  //Add Press to Continue and change to Find that Gil made
  return 0;

}


/*
Function Name: PrintStudentDB
What it does: This function prints all of the students in the student database in ascending order given their IDs.
Parameters and Data Types: No parameters or data types
Return value and data type: Since this is a void function, no value is returned.
*/
void Database::PrintStudentDB(){
  if (studentDB.length() == 0)
    std::cout << "Empty Student Database" << std::endl;
  else
    std::cout << "Student Database:" << std::endl;
    std::cout << " " << std::endl;
    studentDB.inOrder(studentDB.getRoot());
}

/*
Function Name: PrintFacultyDB
What it does: This function prints all of the faculty members in the faculty database in ascending order given their IDs.
Parameters and Data Types: No parameters or data types
Return value and data type: Since this is a void function, no value is returned.
*/
void Database::PrintFacultyDB(){
  if (facultyDB.length() == 0)
    std::cout << "Empty Faculty Database" << std::endl;
  else
    std::cout << "Faculty Database:" << std::endl;
    facultyDB.inOrder(facultyDB.getRoot());
}

/*
Function Name: PrintAdvisor
What it does: This function prints an advisor of a student given the student ID.
Parameters and Data Types: The only parameter is the student ID
Return value and data type: If the student or faculty member does not exist, return -1. Otherwise, return 0.
*/
int Database::PrintAdvisor(int studentID){

  Student* studentTemp = studentDB.find(studentID);
  if(studentTemp == nullptr){
    std::cout << "Student does not exist!" << std::endl;
    return -1;
  }

  if(studentTemp->GetAdvisorID() == -1) {
    std::cout << "Student does not have an advisor" << std::endl;
    return 0;
  }

  Faculty* facultyTemp = facultyDB.find(studentTemp->GetAdvisorID());
  if(facultyTemp == nullptr){
    std::cout <<"Faculty member does not exist!" << std::endl;
    return -1;
  }

  std::cout << studentTemp->GetFullName() << "'s Advisor:" << std::endl;
  facultyTemp->Print();
  //std::cout << facultyTemp->GetName() << " ID: " << studentTemp->GetAdvisorID() << std::endl;
  return 0;
}

/*
Function Name: PrintAdvisor
What it does: This function prints the list of advisees given the faculty ID.
Parameters and Data Types: The only parameter is the faculty ID
Return value and data type: If the faculty member does not exist, return -1. Otherwise, return 0.
*/
int Database::PrintAdvisees(int facultyID){

  Faculty* facultyTemp = facultyDB.find(facultyID);
  if(facultyTemp == nullptr){
    std::cout << "Faculty, " << facultyID << " does not exist." << std::endl;
    return -1;
  }

  if(facultyTemp->studentList.size() == 0){
    std::cout << facultyTemp->GetName() << " does not have any advisees" << std::endl;
  }
  else{
    std::cout << facultyTemp->GetName() << "'s list of advisees:" << std::endl;
    for(int i = 0; i < facultyTemp->studentList.size(); i++){
      Student* studentTemp = studentDB.find(facultyTemp->studentList.at(i));
      if(studentTemp == nullptr){
        std::cout << "Student ID# " << facultyTemp->studentList.at(i) << " does not exist!" << std::endl;
      }
      else{
      studentTemp->Print();
        }
    }
  }

  return 0;
}


/*
Function Name: Rollback
What it does: This function essentially undos the previous change that the user made to either the student or faculty database. The only condition is that
the user can only rollback five consecutive times.
Parameters and Data Types: No parameters or data types
Return value and data type: If the user tries to rollback when there are no changes to undo, return -1. Otherwise, return 0.
*/
int Database::Rollback(){

  if(DBIndicator.length() == 0){
    std::cout << "No Changes to make to the Database" << std::endl;
    return -1;
  }

  std::string Indicator = DBIndicator.removeBack();
  std::cout << Indicator << std::endl;

  if(Indicator == "ADDStudent"){
    studentDB.remove(StudentAdder.removeBack()->GetStudentID());

  } else if(Indicator == "RStudent"){
    AddStudent(StudentAdder.peekBack());
    AddAdvisee(StudentAdder.peekBack()->GetAdvisorID(), StudentAdder.removeBack()->GetStudentID());

  } else if(Indicator == "ADDFaculty"){
    facultyDB.remove(FacultyAdder.removeBack()->GetFacultyID());

  } else if(Indicator == "RFaculty"){
    AddFaculty(FacultyAdder.removeBack());

  } else if(Indicator == "ChangeSAdvisor"){
    RemoveAdvisor(StudentIDs.peekBack());
    std::cout << "We called this!" << std::endl;
    ChangeStudentAdvisor(StudentIDs.removeBack(), FacultyIDs.removeBack());

  } else if(Indicator == "RAdvisee"){
    AddAdvisee(FacultyIDs.removeBack(), StudentIDs.removeBack());
  }

  std::cout << "Rolled Back" << std::endl;
  return 0;
}

/*
Function Name: ReadDB
What it does: This function essentially opens the StudentDB.csv and FacultyDB.csv and reads the information from their respective files. The function then takes this
information and adds it to the student database and faculty database.
Parameters and Data Types: No parameters or data types
Return value and data type: Since this is a void function, no value is returned.
*/
void Database::ReadDB() {

  std::ifstream studentInFS;
  std::ifstream facultyInFS;

  studentInFS.open("DatabaseFiles/StudentDB.csv");
  facultyInFS.open("DatabaseFiles/FacultyDB.csv");

  while (!studentInFS.eof()) {
    Student* student = new Student();
    studentInFS >> *student;
    AddStudent(student);
  }

  while (!facultyInFS.eof()) {
    Faculty* faculty = new Faculty();
    facultyInFS >> *faculty;
    AddFaculty(faculty);
  }

  studentInFS.close();
  facultyInFS.close();
}

/*
Function Name: WriteDB
What it does: This function essentially opens the StudentDB.csv and FacultyDB.csv and writes the information from the student
database and faculty database into their respective files.
Parameters and Data Types: No parameters or data types
Return value and data type: Since this is a void function, no value is returned.
*/
void Database::WriteDB() {

  std::ofstream studentOutFS;
  std::ofstream facultyOutFS;

  studentOutFS.open("DatabaseFiles/StudentDB.csv");
  facultyOutFS.open("DatabaseFiles/FacultyDB.csv");

  while (!studentDB.isEmpty()) {
    studentOutFS << *(studentDB.find(studentDB.getMin()->key));
    studentDB.remove(studentDB.getMin()->key);
    if (!studentDB.isEmpty()) {
      studentOutFS << std::endl;
    }
  }

  while (!facultyDB.isEmpty()) {
    facultyOutFS << *(facultyDB.find(facultyDB.getMin()->key));
    facultyDB.remove(facultyDB.getMin()->key);
    if (!facultyDB.isEmpty()) {
      facultyOutFS << std::endl;
    }
  }

  studentOutFS.close();
  facultyOutFS.close();
}


/*
Function Name: PrintPrompt
What it does: This function allows for the user to see the menu right after they make a change so that they don't
have to remember all the options.
Parameters and Data Types: No parameters or data types
Return value and data type: Since this is a void function, no value is returned.
*/
void Database::PrintPrompt(){

  std::cout << "Menu, select by number choice:" << std::endl;
  std::cout << "[1]  Print Student Database" << std::endl;
  std::cout << "[2]  Print Faculty Database" << std::endl;
  std::cout << "[3]  Find & Print Student" << std::endl;
  std::cout << "[4]  Find & Print Faculty" << std::endl;
  std::cout << "[5]  Print Student's Advisor" << std::endl;
  std::cout << "[6]  Print Faculty's Advisees" << std::endl;
  std::cout << "[7]  Remove Student" << std::endl;
  std::cout << "[8]  Remove Faculty" << std::endl;
  std::cout << "[9]  Add Student" << std::endl;
  std::cout << "[10] Add Faculty" << std::endl;
  std::cout << "[11] Change a Student's Advisor" << std::endl;
  std::cout << "[12] Remove a Faculty's Advisee" << std::endl;
  std::cout << "[13] Rollback" << std::endl;
  std::cout << "[14] Exit" << std::endl;

}

/*
Function Name: PressToContinue
What it does: This function gives the ability for the user to look at the results and then press any key for the menu
to display again.
Parameters and Data Types: No parameters or data types
Return value and data type: Since this is a void function, no value is returned.
*/
void Database::PressToContinue(){
  std::string key = "";
  std::cout << "Press any key to continue" << std::endl;
  getline(std::cin, key);
  getline(std::cin, key);
}


/*
Function Name: Menu
What it does: This function essentially displays all of the users options and what they want to do with the student database and
faculty database. It gives them the opportunity to make any changes to either database or display information that is contained
in either the student database or faculty database.
Parameters and Data Types: No parameters or data types
Return value and data type: Since this is a void function, no value is returned.
*/
void Database::Menu() {

  ReadDB();

  std::string name = "";
  std::string level = "";
  std::string major = "";
  std::string department = "";
  std::string enter = " ";
  double gpa = 0.0;
  int advisorID = 0;
  int option = 0;
  int studentIDNumber = 0;
  int facultyIDNumber = 0;

  std::cout << "Welcome to the Student Database!" << std::endl;
  PrintPrompt();
  std::cin >> option;

  while (option != 14) {

    if(option == 1){
      PrintStudentDB();
      PressToContinue();

    } else if(option == 2){
      PrintFacultyDB();
      PressToContinue();

    } else if(option == 3){

      std::cout << "Type in the student ID: ";
      std::cin >> studentIDNumber;
      FindStudent(studentIDNumber);
      PressToContinue();

    } else if(option == 4){

      std::cout << "Type in the faculty member ID: ";
      std::cin >> facultyIDNumber;

      while(FindFaculty(facultyIDNumber) == -1) {
        std::cout << "Incorrect ID! Try again or input -1 to exit";
        std::cin >> facultyIDNumber;
        if (facultyIDNumber == -1)
          break;
      }
      PressToContinue();

    } else if(option == 5){

      std::cout << "Type in the student ID to display name and info of faculty advisor: ";
      std::cin >> studentIDNumber;

      while(PrintAdvisor(studentIDNumber) == -1){
        std::cout << "Enter another student ID or -1 to exit: ";
        std::cin >> studentIDNumber;
        if(studentIDNumber == -1){
          break;
        }
      }
      PressToContinue();

    } else if(option == 6){

      std::cout << "Type in the faculty ID to display all names and info of advisees: ";
      std::cin >> facultyIDNumber;

      while(PrintAdvisees(facultyIDNumber) == -1){
        std::cout << "Emter another faculty ID or -1 to exit: ";
        std::cin >> facultyIDNumber;
        if(facultyIDNumber == -1){
          break;
        }
      }
      PressToContinue();

    } else if(option == 7){

      DBIndicator.insertBack("RStudent");
      this->RollBackCounter = 0;

      std::cout << "Enter a Student ID: ";
      std::cin >> studentIDNumber;

      Student* studentTemp = studentDB.find(studentIDNumber);
      if (studentTemp != nullptr) {
        StudentAdder.insertBack(studentTemp);
      }

      RemoveStudent(studentIDNumber);

    } else if(option == 8) {

      DBIndicator.insertBack("RFaculty");
      this->RollBackCounter = 0;

      std::cout << "Enter a Faculty ID: ";
      std::cin >> facultyIDNumber;

      Faculty* facultyTemp = facultyDB.find(facultyIDNumber);
      if (facultyTemp != nullptr) {
        FacultyAdder.insertBack(facultyTemp);
      }

      RemoveFaculty(facultyIDNumber);

    } else if(option == 9) {

      DBIndicator.insertBack("ADDStudent");
      this->RollBackCounter = 0; //Options 7 - 12 are only ones that change the database, so once one of those options are selected, RollBackCounter will be reset to 0.

      std::cout << "Enter a Student ID: ";
      std::cin >> studentIDNumber;
      std::cin.ignore();

      std::cout << "Enter a Name: ";
      getline(std::cin, name);
      std::cin.sync();

      std::cout << "Enter a Level: ";
      getline(std::cin, level);

      std::cout << "Enter a Major: ";
      getline(std::cin, major);

      std::cout << "Enter a GPA: ";
      std::cin >> gpa;

      std::cout << "Enter an Advisor Number: ";
      std::cin >> advisorID;

      Student* student = new Student(studentIDNumber, name, level, major, gpa, advisorID);
      StudentAdder.insertBack(student);
      AddStudent(student);
      if (ChangeStudentAdvisor(studentIDNumber, advisorID) == -1) { student->SetAdvisorID(-1); }

    } else if(option == 10) {

      DBIndicator.insertBack("ADDFaculty");
      this->RollBackCounter = 0;
      studentIDNumber = 0;

      std::cout << "Enter a Faculty ID: ";
      std::cin >> facultyIDNumber;
      std::cin.ignore();

      std::cout << "Enter a Name: ";
      getline(std::cin, name);
      std::cin.sync();

      std::cout << "Enter a Level: ";
      std::getline(std::cin, level);

      std::cout << "Enter a Department: ";
      getline(std::cin, department);

      Faculty* advisor = new Faculty(facultyIDNumber, name, level, department);
      FacultyAdder.insertBack(advisor);
      AddFaculty(advisor);

    } else if(option == 11) {

      DBIndicator.insertBack("ChangeSAdvisor");
      this->RollBackCounter = 0;

      std::cout << "Enter a new Faculty ID: ";
      std::cin >> facultyIDNumber;

      std::cout << "Enter a Student ID: ";
      std::cin >> studentIDNumber;

      Student* studentTemp = studentDB.find(studentIDNumber);
      if(studentTemp != nullptr){
        StudentIDs.insertBack(studentIDNumber);
        FacultyIDs.insertBack(studentTemp->GetAdvisorID());
      }
      ChangeStudentAdvisor(studentIDNumber, facultyIDNumber);

    } else if(option == 12) {

      DBIndicator.insertBack("RAdvisee");
      this->RollBackCounter = 0;

      std::cout << "Enter a Faculty ID: ";
      std::cin >> facultyIDNumber;

      std::cout << "Enter a Student ID: ";
      std::cin >> studentIDNumber;

      Faculty* facultyTemp = facultyDB.find(facultyIDNumber);
      if(facultyTemp != nullptr){
        if(facultyTemp->HasStudent(studentIDNumber)){
          FacultyIDs.insertBack(facultyIDNumber);
          StudentIDs.insertBack(studentIDNumber);
        }
      }
      RemoveAdvisee(facultyIDNumber, studentIDNumber);

    } else if(option == 13) {

      this->RollBackCounter++;
      if(this->RollBackCounter > 5){
        std::cout << "You can't Rollback more than five consecutive times. " << std::endl;
      } else {
        Rollback();
      }

      PressToContinue();

    } else if(option > 14 || option < 1) {
      PrintPrompt();
      std::cout << "Wrong Input! " << std::endl;
    }

    PrintPrompt();
    std::cout << "Choose Again: ";
    std::cin >> option;
  }



  WriteDB();
}
