// 提交编号: 757606598
// 提交时间: 2026-10-29 15:38:22
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        int min=10^6;
        if(root->left==nullptr && root->right==nullptr){
            return min;
        }
        if(root->left!=nullptr){
            min=std::min(root->val-root->left->val,min);
            min=std::min(min,getMinimumDifference(root->left));
        }
        if(root->right!=nullptr){
            min=std::min(root->right->val-root->val,min);
            min=std::min(min,getMinimumDifference(root->right));
        }
        return min;
    }
};