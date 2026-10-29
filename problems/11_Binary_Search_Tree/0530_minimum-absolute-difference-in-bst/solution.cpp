/**
 * 题目: 530. 二叉搜索树的最小绝对差
 * 链接: https://leetcode.cn/problems/minimum-absolute-difference-in-bst/
 * 难度: 简单
 * 
 * 当前状态: 🟡 调试修复中 (提交 757606598 报 Wrong Answer)
 */

#include <algorithm>
#include <climits>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * ============================================================================
 * 版本 1: 用户初始提交版本 (WA, 记录核心踩坑点)
 * ============================================================================
 * 踩坑点 1: int min = 10^6; 在 C++ 中是按位异或运算，结果为 12！
 * 踩坑点 2: 仅对比了直接左右孩子，未考虑跨层祖孙节点（如左子树的最右节点是根节点的前驱）
 */
class SolutionWrong {
public:
    int getMinimumDifference(TreeNode* root) {
        int min = 10^6; // ⚠️ Bug: 10 XOR 6 = 12
        if (root->left == nullptr && root->right == nullptr) {
            return min;
        }
        if (root->left != nullptr) {
            min = std::min(root->val - root->left->val, min);
            min = std::min(min, getMinimumDifference(root->left));
        }
        if (root->right != nullptr) {
            min = std::min(root->right->val - root->val, min);
            min = std::min(min, getMinimumDifference(root->right));
        }
        return min;
    }
};

/**
 * ============================================================================
 * 版本 2: 标准最优解 (BST 中序遍历双指针)
 * ============================================================================
 * 核心考点: 
 * BST 的核心本质是【中序遍历（左中右）结果是一个严格递增的有序序列】。
 * 在一个有序序列中，最小绝对差必定只出现在【任意两个相邻元素】之间！
 * 
 * 复杂度:
 * - 时间复杂度: O(N)，每个节点仅访问一次
 * - 空间复杂度: O(H)，递归系统调用栈深度，最好 O(log N)，最坏 O(N)
 */
class Solution {
private:
    int minDiff = INT_MAX;
    TreeNode* prev = nullptr; // 记录中序遍历的前一个节点指针

    void inOrder(TreeNode* root) {
        if (!root) return;

        // 1. 递归遍历左子树
        inOrder(root->left);

        // 2. 处理当前根节点：与前驱节点对比差值
        if (prev != nullptr) {
            minDiff = std::min(minDiff, root->val - prev->val);
        }
        prev = root; // 更新前驱指针为当前节点

        // 3. 递归遍历右子树
        inOrder(root->right);
    }

public:
    int getMinimumDifference(TreeNode* root) {
        minDiff = INT_MAX;
        prev = nullptr;
        inOrder(root);
        return minDiff;
    }
};
