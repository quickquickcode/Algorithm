// 提交编号: 757310144
// 提交时间: 2026-10-27 22:01:06
// 判题结果: Accepted
// 运行时间: 0 ms | 内存: 14.8 MB

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
    vector<int> rightSideView(TreeNode* root) {
        vector<TreeNode*> list{};

        vector<int> result{};

        if(root==nullptr){
            return result;
        }
        list.push_back(root);
        result.push_back(list[0]->val);
        vector<TreeNode*> temp{};

        while (list.size()!=0){
            int point=0;
            for(int i=0; i<list.size(); i++){
                if(list[i]->left){
                    temp.push_back(list[i]->left);
                    point++;
                }
                if(list[i]->right){
                    temp.push_back(list[i]->right);
                    point++;
                }
            }
            if(point){
                result.push_back(temp[point-1]->val);
            }
            list=temp;
            temp.clear();
        }
        return result;
    }
};