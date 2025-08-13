// mainprogram to test out the BST functions
#include "BST.h"
#include "TreeNode.h"
#include "../Student.h"
#include "../Faculty.h"
#include <iostream>

/*int main(){
  // creating BST object and running some functions 

  Student* student = new Student(1801, "Gilberto A", "Fresh", "Comp Sci", 3.4);
  Student* stu2 = new Student(1800, "First Student", "Soph", "SE", 2.4);
  Student* stu3 = new Student(1804, "Third Stu", "senior", "Comp Sci", 3.4);

  Faculty* fac1 = new Faculty(11, "Rao Linstead", "Dean", "CS");
  Faculty* fac2 = new Faculty(12, "Elizabeth Junior", "CEO", "Chemical");
  Faculty* fac3 = new Faculty(13, "Joe Biden", "President", "SE");
  Faculty* fac4 = new Faculty(14, "My Leg", "Bar", "Foo");

  BST<Student*> aTree;
  BST<Faculty*> facTree;

  aTree.insert(new TreeNode<Student*>(stu3->GetStudentID(), stu3));
  aTree.insert(new TreeNode<Student*>(stu2->GetStudentID(), stu2));
  aTree.insert(new TreeNode<Student*>(student->GetStudentID(), student));
  aTree.inOrder(aTree.getRoot());

  std::cout << std::endl;

  facTree.insert(new TreeNode<Faculty*>(fac1->GetFacultyID(), fac1));
  facTree.insert(new TreeNode<Faculty*>(fac2->GetFacultyID(), fac2));
  facTree.insert(new TreeNode<Faculty*>(fac3->GetFacultyID(), fac3));
  facTree.insert(new TreeNode<Faculty*>(fac4->GetFacultyID(), fac4));
  facTree.inOrder(facTree.getRoot());

  BST<int> myBST;
  myBST.insert(new TreeNode<int>(2,2));
  myBST.insert(new TreeNode<int>(1,1));
  myBST.insert(new TreeNode<int>(10,10));
  myBST.insert(new TreeNode<int>(5,5));
  myBST.printTree(std::cout);
  myBST.remove(5);
  myBST.printTree(std::cout);
  myBST.remove(1);
  myBST.printTree(std::cout);
  myBST.remove(2);
  myBST.printTree(std::cout);
  cout << myBST.contains(10) << endl;
  myBST.remove(10);
  myBST.printTree(std::cout);
  cout << myBST.contains(10) << endl;

  return 0;
}*/