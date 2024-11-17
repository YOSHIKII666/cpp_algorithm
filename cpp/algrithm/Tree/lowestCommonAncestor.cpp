struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode():val(0),left(nullptr),right(nullptr){};
    TreeNode(int x):val(x),left(nullptr),right(nullptr){};
    TreeNode(int x ,TreeNode* left,TreeNode* right):val(x),left(left),right(right){};
};

class Solution{
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root,TreeNode* p,TreeNode* q){
            if(root==nullptr||root==p||root==q){
                return root;
            }
            TreeNode* left=root->left==nullptr?nullptr:lowestCommonAncestor(root->left,p,q);
            TreeNode* right=root->right==nullptr?nullptr:lowestCommonAncestor(root->right,p,q);
            if(left!=nullptr&&right!=nullptr) return root;
            if(left==nullptr) return right;
            if(right==nullptr) return left;
            return nullptr;
        }
};
