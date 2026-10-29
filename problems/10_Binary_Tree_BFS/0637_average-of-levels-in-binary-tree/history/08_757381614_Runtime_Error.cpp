// 提交编号: 757381614
// 提交时间: 2026-10-28 12:00:42
// 判题结果: Runtime Error
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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> result={};
        vector<TreeNode*> list={};
        if (root==nullptr){
            return result;
        }
        list.push_back(root);

        vector<TreeNode*> temp={};
        while (list.size() != 0){
            int layer_sum=0;
            for(int i = 0; i<list.size(); i++){
                if(list[i]->left != nullptr){
                    temp.push_back(list[i]->left);
                }
                if(list[i]->right != nullptr){
                    temp.push_back(list[i]->right);
                }
                layer_sum+=list[i]->val;
            }
            result.push_back((double) layer_sum/list.size());

            list.clear();
            list=temp;
            temp.clear();
        }
        return result;
    }
};