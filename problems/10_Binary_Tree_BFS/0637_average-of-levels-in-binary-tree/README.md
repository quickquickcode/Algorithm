# [637. Average of Levels in Binary Tree] 二叉树的层平均值

- **力扣链接**：[637. 二叉树的层平均值](https://leetcode.cn/problems/average-of-levels-in-binary-tree/)
- **所属专题**：面试经典 150 题 - 二叉树层次遍历 (Binary Tree BFS)
- **难度**：🟢 简单
- **做题时间**：2026-10-28 11:54 ~ 12:02
- **最终成绩**：✅ Accepted | 运行时间: **0 ms**（击败 100.00%） | 内存: 23.6 MB
- **掌握状态**：🟢 一次通过（经历了队列层序与求和数值溢出防御等优化）
- **历史提交记录目录**：[history/](history/)
- **题解代码**：[solution.cpp](solution.cpp)

---

## 1. 题目大意与核心考点

给定一个非空二叉树的根节点 `root` , 以数组的形式返回每一层节点的平均值。与真实答案误差在 $10^{-5}$ 以内的答案将被视为正确答案。

- **核心考点**：
  1. **层序遍历（BFS）模板**：使用队列按层推进。
  2. **数值溢出防范**：节点值在 $[-2^{31}, 2^{31} - 1]$ 范围，层节点求和必须使用 `double` 或 `long long` 累加，否则多节点相加会触发整数溢出！

---

## 2. 标杆题解

```cpp
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        if (!root) return res;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            double sum = 0;
            for (int i = 0; i < sz; ++i) {
                TreeNode* node = q.front();
                q.pop();
                sum += node->val;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            res.push_back(sum / sz);
        }
        return res;
    }
};
```
