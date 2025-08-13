#ifndef TREENODE_H
#define TREENODE_H

template <typename E>
class TreeNode {
    public:
        E value;
        int key;
        TreeNode* left;
        TreeNode* right;

        TreeNode() {
            key = 0;
            value = E();
            left = nullptr;
            right = nullptr;
        }

        TreeNode(int key, E value) {
            this->key = key;
            this->value = value;
            left = nullptr;
            right = nullptr;
        }
};

#endif