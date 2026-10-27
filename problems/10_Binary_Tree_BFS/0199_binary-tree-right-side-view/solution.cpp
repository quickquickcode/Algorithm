// 199. 二叉树的右视图 (Binary Tree Right Side View)
// 核心解法：二叉树层序遍历 (BFS) / 队列分层 or 双缓冲
// 时间复杂度：O(N)，空间复杂度：O(D) 其中 D 为树的最大宽度
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 解法一：标准单队列层序遍历（推荐，工业级标准）
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int level_size = q.size(); // 当前层的节点总数

            for (int i = 0; i < level_size; ++i) {
                TreeNode* node = q.front();
                q.pop();

                // 核心：如果是当前层的最后一个节点，那就是从右侧看到的节点
                if (i == level_size - 1) {
                    result.push_back(node->val);
                }

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }

        return result;
    }
};

// 解法二：双缓冲 Vector 模拟层序遍历（你的 0ms AC 解法）
class SolutionDoubleBuffer {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        vector<TreeNode*> cur_level = {root};
        result.push_back(root->val);

        while (!cur_level.empty()) {
            vector<TreeNode*> next_level;
            for (TreeNode* node : cur_level) {
                if (node->left) next_level.push_back(node->left);
                if (node->right) next_level.push_back(node->right);
            }
            // 只要下一层存在节点，取下一层的末尾元素就是右视图
            if (!next_level.empty()) {
                result.push_back(next_level.back()->val);
            }
            cur_level = std::move(next_level);
        }

        return result;
    }
};
