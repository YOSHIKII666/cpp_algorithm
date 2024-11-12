#include<vector>
struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    int val;
    TreeNode():val(0),left(nullptr),right(nullptr){};
    TreeNode(int x):val(x),left(nullptr),right(nullptr){};
    TreeNode(int x,TreeNode* left,TreeNode* right):val(0),left(left),right(right){};
};

class solution{
    public:
    int sum=0;
    std::vector<int> list;
    std::vector<std::vector<int>> res;
    int targetSum;
     std::vector<std::vector<int>> pathSum(TreeNode* root,int targetSum){
        this->targetSum=targetSum;
        dfs(root);
        return res;
     }
     void dfs(TreeNode* root){
        if(root==nullptr) return;
        sum+=root->val;
        list.push_back(root->val);
        if(sum==targetSum&&root->left==nullptr&&root->right==nullptr){
            res.push_back(list);
        }
        dfs(root->left);
        dfs(root->right);
        //»ØËÝ`1
        sum-=root->val;
        list.pop_back();
     }
};