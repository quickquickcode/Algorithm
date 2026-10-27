// 提交编号: 757307938
// 提交时间: 2026-10-27 21:51:39
// 判题结果: Compile Error
// 运行时间: N/A | 内存: N/A

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
        vector<TreeNode> list{};
        vector<TreeNode> right{};
        vector<int> result{};
        list.push_back(root);
        result.push_back(list[0].val);

        while (list.empty()){
            vector<TreeNode> temp{};
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
            result.push_back(list[point-1].val);
            list=temp;
        }
        return result;
    }
};