#include <climits>
#include <bits/algorithmfwd.h>
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode():val(0),left(nullptr),right(nullptr){};
    TreeNode(int x):val(x),left(nullptr),right(nullptr){};
    TreeNode(int x,TreeNode* left,TreeNode* right):val(x),left(nullptr),right(nullptr){};
};

class solution{
    public:
        int max=INT_MIN; 
        int maxSum(TreeNode* root){
            dfs(root);
            return max;
        }
        int dfs(TreeNode* root){
            if(root==nullptr) return 0;
            int left=dfs(root->left);
            int right=dfs(root->right);
            max=std::max(left+right+root->val,max);
            int cur=std::max(left,right)+root->val;
            return cur>0?cur:0;
        }
};