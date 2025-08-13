#ifndef BST_H
#define BST_H
// template class for BST

#include "TreeNode.h"
#include <ostream>
#include "../Student.h"
#include "../Faculty.h"
#include <iostream>

template <typename E>
class BST{
private:
  TreeNode<E>* root; // root of tree
  TreeNode<E>* curr;
  int size; // number of elements in tree

public:
  BST();
  ~BST();

  TreeNode<E>* getSuccessor(TreeNode<E>* d);
  TreeNode<E>* getMin();
  TreeNode<E>* getMax();

  void insert(TreeNode<E>* node);
  bool remove(int k);
  bool contains(int k);
  E find(int k);

  void inOrder(TreeNode<Student*>* node);
  void inOrder(TreeNode<Faculty*>* node);

  void write(TreeNode<Student*>* node, std::ostream& out);
  void write(TreeNode<Faculty*>* node, std::ostream& out);

  void printTree(std::ostream& stream);
  TreeNode<E>* getRoot();

  int length();
  bool isEmpty();

};


/*
Constructor, sets root and size values.
*/
template <typename E>
BST<E>::BST(){
  root = nullptr;
  curr = root;
  size = 0;
}

/*
Destructor
*/
template <typename E>
BST<E>::~BST(){

}

/*
contains
Checks if tree contains node with key k.
@param k: key to find.
@return T/F
*/
template <typename E>
bool BST<E>::contains(int k){

  if (root == nullptr) {
    return false;
  }
  TreeNode<E>* curr = root;

  while (curr->key != k) { // loop to keep iterating through the tree
    if (k < curr->key) { 
      curr = curr->left;
    } else {
      curr = curr->right;
    }

    if (curr == nullptr) { // if we reached an empty pointer, then the key was never found
      return false;
    }
  }
  return true; // if we exit the while loop, thus the key was found
}

template <typename E>
E BST<E>::find(int k){

  if (root == nullptr) {
    return E();
  }
  TreeNode<E>* curr = root;

  while (curr->key != k) {
    if (k < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }

    if (curr == nullptr) {
      return E();
    }
  }
  return curr->value;
}

/*
insert
Inserts node in tree.
@param node: tree node to insert.
*/
template <typename E>
void BST<E>::insert(TreeNode<E>* node){

  if (root == nullptr) {
    root = node;
  } else {
    TreeNode<E>* curr = root;
    TreeNode<E>* parent;

    while (true) {
      parent = curr;

      if (node->key < curr->key) {

        curr = curr->left;
        if (curr == nullptr) {
          parent->left = node;
          break;
        }

      } else {

        curr = curr->right;
        if (curr == nullptr) {
          parent->right = node;
          break;
        }

      }
    }
  }

  size++;
}


/*
delete
Delete a node from tree.
@param k: key to find and delete.
@return T/F whether delete was successful.
*/
template <typename E>
bool BST<E>::remove(int k){

  if (root == nullptr) {
    return false;
  }
  TreeNode<E>* curr = root;
  TreeNode<E>* parent;
  bool isLeft = true; // determines if the curr node is a left or right child of the parent

  // locate the node to delete
  while (curr->key != k) { 
    parent = curr;

    if (k < curr->key) { 
      isLeft = true;
      curr = curr->left;
    } else {
      isLeft = false;
      curr = curr->right;
    }

    if (curr == nullptr) { // we could not find the key to delete
      return false;
    }
  }
  // at this point, we have found the node to remove

  // case 1: curr node has no children
  if (curr->left == nullptr && curr->right == nullptr) {
    if (curr == root) {
      root = nullptr;
    } else if (isLeft) {       // if the curr node is the parent's left child
      parent->left = nullptr;  // thus the parent's left child is removed
    } else {
      parent->right = nullptr; // otherwise parent's right child is removed
    }
    return true;
  }
  // Since we are continuing from the previous condition, we can know there is at least a left or right child
  // case 2: curr node has 1 left child
  else if (curr->right == nullptr) { 
    if (curr == root) {
      root = curr->left;
    } else if (isLeft) {
      parent->left = curr->left;
    } else {
      parent->right = curr->left;
    }
  }

  // case 3: curr node has 1 right child
  else if (curr->left == nullptr) { 
    if (curr == root) {
      root = curr->right;
    } else if (isLeft) {
      parent->left = curr->right;
    } else {
      parent->right = curr->right;
    }
  }

  // case 4: curr node has 2 children
  else {
    TreeNode<E>* successor = getSuccessor(curr);

    if (curr == root) {
      root = successor;
    } else if (isLeft) {
      parent->left = successor;
    } else {
      parent->right = successor;
    }

    successor->left = curr->left; // no matter the outcome of what curr is, we will replace the succesor's left w/ curr's left
  }

  size--;
  delete curr;
  return true;

}

/*
getSuccessor
Find a node's left most child of its right child
@param d: Node to find successor for.
@return successor node.
*/
template <typename E>
TreeNode<E>* BST<E>::getSuccessor(TreeNode<E>* d){
  TreeNode<E>* succerosParent = d;
  TreeNode<E>* successor = d;
  TreeNode<E>* curr = d->right;

  while (curr != nullptr) {
    succerosParent = successor;
    successor = curr;
    curr = curr->left;
  }

  if (successor != d->right) {
    succerosParent->left = successor->right;
    successor->right = d->right;
  }
  return successor;

}

/*
getMin
Find a tree's smallest key node.
@return smallest key node
*/
template <typename E>
TreeNode<E>* BST<E>::getMin(){
  TreeNode<E>* curr = root;

  if (root == nullptr)
    return new TreeNode<E>();

  while (curr->left != nullptr) // go to the far left value, which would be the max due to the nature of the bst
    curr = curr->left;

  return curr;

}


/*
getMax
Find a tree's largest key node.
@return largest key node
*/
template <typename E>
TreeNode<E>* BST<E>::getMax(){
  TreeNode<E>* curr = root;

  if (root == nullptr)
    return new TreeNode<E>();

  while (curr->right!= nullptr) // go to the far right value, which would be the max due to the nature of the bst
    curr = curr->right;

  return curr;

}

/*
inOrder
Inorder traversal starting at some node.
@param node: node to begin traversal
*/
/*template <typename I>
//void BST<I>::inOrder(TreeNode<I>* node) {

  if (node == nullptr) {
    return;
  }

  inOrder(node->left);
  stream << node->key << "-";
  inOrder(node->right);

}*/

template <typename E>
void BST<E>::inOrder(TreeNode<Student*>* node) {

  if (node == nullptr) {
    return;
  }

  inOrder(node->left);
  (node->value)->Print();
  inOrder(node->right);

}

template <typename E>
void BST<E>::inOrder(TreeNode<Faculty*>* node) {

  if (node == nullptr) {
    return;
  }

  inOrder(node->left);
  (node->value)->Print();
  inOrder(node->right);

}

template <typename E>
void BST<E>::write(TreeNode<Student*>* node, std::ostream& out) { 

  if (node == nullptr) {
    return;
  }

  inOrder(node->left);
  std::cout << "We are here!" << std::endl;
  out << (*(node->value));
  inOrder(node->right);

}

template <typename E>
void BST<E>::write(TreeNode<Faculty*>* node, std::ostream& out) {

  if (node == nullptr) {
    return;
  }

  inOrder(node->left);
  out << (node->value);
  inOrder(node->right);

}


/*
printTree
Caller for inOrder.
*/
template <typename E>
void BST<E>::printTree(std::ostream& stream){
  inOrder(root);
  stream << std::endl;
}

/*
getRoot
@return root: root of tree.
*/
template <typename E>
TreeNode<E>* BST<E>::getRoot(){
  return root;
}

/*
length
@return size: size of tree.
*/
template <typename E>
int BST<E>::length(){
  return size;
}

/*
isEmpty
@return T/F: if size is 0 or not.
*/
template <typename E>
bool BST<E>::isEmpty(){
  return (size == 0 || root == nullptr);
}


#endif