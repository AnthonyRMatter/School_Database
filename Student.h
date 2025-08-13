// Author: Gilberto Arellano
#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
    private:
        int studentID;
        std::string fullName;
        std::string grade;
        std::string major;
        double gpa;
        int advisorID;
   
    public:
        Student() {
            this->studentID = -1;
            this->fullName = "";
            this->grade = "";
            this->major = "";
            this->gpa = 0.0;
            this->advisorID = 0;
        }
        Student(int studentID, std::string fullName, std::string grade, std::string major, double gpa) {
            this->studentID = studentID;
            this->fullName = fullName;
            this->grade = grade;
            this->major = major;
            this->gpa = gpa;    
            this->advisorID = -1;
            }
        Student(int studentID, std::string fullName, std::string grade, std::string major, double gpa, int advisorID) {
            this->studentID = studentID;
            this->fullName = fullName;
            this->grade = grade;
            this->major = major;
            this->gpa = gpa;    
            this->advisorID = advisorID;
            }
        ~Student() { };

        void SetStudentID(int studentID) { this->studentID = studentID; }
        void SetFullName(std::string fullName ) { this->fullName = fullName; }
        void SetGrade(std::string grade) { this->grade = grade; }
        void SetMajor(std::string major) { this->major = major; }
        void SetGPA(double gpa) { this->gpa = gpa; }
        void SetAdvisorID(int advisorID) { this->advisorID = advisorID; }

        int GetStudentID() { return this->studentID; }
        std::string GetFullName() { return this-> fullName; }
        std::string GetGrade() { return this->grade; }
        std::string GetMajor() { return this->major; }
        double GetGPA() { return this->gpa; } 
        int GetAdvisorID() { return this->advisorID; }

        void Print();
        std::string ToString();

        bool operator==(Student rhs) { return (this->studentID == rhs.studentID); }
        bool operator>(Student rhs) { return (this->studentID > rhs.studentID); }
        bool operator<(Student rhs) { return (this->studentID < rhs.studentID); }

        friend std::ostream& operator<<(std::ostream& out, Student& student);
        friend std::istream& operator>>(std::istream& in, Student& student);


};

#endif