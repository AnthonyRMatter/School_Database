#ifndef DATABASE_H
#define DATABASE_H

#include "Datastructures/BST.h"
#include "Datastructures/DLList.h"
#include "Datastructures/TreeNode.h"
#include "Student.h"
#include "Faculty.h"
#include <vector>
#include <string>
#include <stack>

class Database {
    public:
        Database() { };
        ~Database() { }

        BST<Student*> studentDB;
        BST<Faculty*> facultyDB;
        int RollBackCounter = 0;

        DLList<std::string> DBIndicator;
        DLList<Student*> StudentAdder;
        DLList<Faculty*> FacultyAdder;
        DLList<int> StudentIDs;
        DLList<int> FacultyIDs;

        void AddStudent(Student* student);
        void AddFaculty(Faculty* faculty);
        int AddAdvisee(int facultyID, int studentID);
        int AddAdvisor(int studentID, int newFacultyID);

        int ChangeStudentAdvisor(int studentID, int newFacultyID);
        int RemoveAdvisee(int facultyID, int studentID);
        int RemoveAdvisor(int studentID);
        int RemoveStudent(int studentID);
        int RemoveFaculty(int facultyID);

        int FindStudent(int studentID);
        int FindFaculty(int facultyID);

        void PrintStudentDB();
        void PrintFacultyDB();
        int PrintAdvisor(int studentID);
        int PrintAdvisees(int facultyID);

        void Menu();
        int Rollback();
        void PrintPrompt();
        void PressToContinue();
        void ReadDB();
        void WriteDB();

    private:

};

#endif
