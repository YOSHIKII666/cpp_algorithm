//
// Created by 王少泽 on 2024/11/16.
//

#include <algorithm>

struct TreeNode {
    TreeNode* right;
    TreeNode* left;
    int val;
    TreeNode():val(0),right(nullptr),left(nullptr){};
    TreeNode(int x):val(x),right(nullptr),left(nullptr){};
    TreeNode(int x,TreeNode* left,TreeNode* right):val(x),left(left),right(right){};
};

class solution {
    bool avl(TreeNode* root) {
        if(root==nullptr) return true;
        return std::abs(depth(root->left)-depth(root->right)<=1)&&avl(root->left)&&avl(root->right);
    }
    int depth(TreeNode* root) {
        if(root==nullptr) return 0;
        return std::max(depth(root->left)+1,depth(root->right)+1);
    }
};
