# [199. Binary Tree Right Side View] 二叉树的右视图

- **力扣链接**：[199. 二叉树的右视图](https://leetcode.cn/problems/binary-tree-right-side-view/)
- **所属专题**：面试经典 150 题 - 二叉树层次遍历 (Binary Tree BFS)
- **难度**：🟡 中等（树层序遍历高频代表作）
- **做题时间**：2026-10-27 21:51 ~ 22:01（历时 10 分钟，13 次提交完成层序双缓冲攻坚）
- **最终成绩**：✅ Accepted | 运行时间: **0 ms**（击败 100%） | 内存: 14.8 MB
- **掌握状态**：🟢 一次通过（攻克指针语法、空树特判与负索引越界，成功实现双缓冲层序遍历）
- **历史提交记录目录**：[history/](history/)

---

## 1. 题目大意与核心特征

- **一句话题意**：给定一个二叉树的根节点 `root`，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
- **视觉本质**：
  从右侧看二叉树，所能看到的每一个节点，**恰好就是每一层二叉树从左往右遍历时的最后一个节点**！
- **核心考点**：二叉树层序遍历（BFS）、指针与对象语义、空树边界特判。

---

## 2. 真实提交迭代轨迹（10 分钟 13 次演变实录）

从 21:51:11 到 22:01:06，这 10 分钟的 13 次提交展现了一个极其典型的二叉树进阶轨迹：**指针类型 $\rightarrow$ 循环语义 $\rightarrow$ 变量混淆 $\rightarrow$ 越界防崩 $\rightarrow$ 空树防御 $\rightarrow$ AC**：

| 提交序号 | 提交编号 | 判题状态 | 提交时间 | 核心特征与错因剖析 | 源码切片链接 |
| :---: | :---: | :---: | :---: | :--- | :---: |
| **01~04** | `757307851~131` | ❌ Compile Error | 21:51~52 | **C++ 指针类型混淆**：混淆了 `TreeNode` 与 `TreeNode*`；混用了点号 `.` 与箭头 `->` | [01_757307851_Compile_Error.cpp](history/01_757307851_Compile_Error.cpp) |
| **05~06** | `757308355~469` | ❌ Wrong Answer | 21:53 | **循环条件写反**：误写成 `while (list.empty())`，因为 list 不为空，循环一次都没进！ | [05_757308355_Wrong_Answer.cpp](history/05_757308355_Wrong_Answer.cpp) |
| **07~09** | `757308811~134` | ❌ CE / WA | 21:55~56 | 改正 `while (list.size() != 0)`，但取值误写成了 `list[point-1]`（取了上一层而非当前层） | [08_757308897_Wrong_Answer.cpp](history/08_757308897_Wrong_Answer.cpp) |
| **10~11** | `757309319~421` | ❌ **Runtime Error** | 21:57 | 改为 `temp[point-1]`，但到了叶子层时下一层无节点（`point=0`），访问 `temp[-1]` 越界崩溃！ | [10_757309319_Runtime_Error.cpp](history/10_757309319_Runtime_Error.cpp) |
| **12** | `757309872` | ❌ **Runtime Error** | 21:59:47 | 加上了 `if (point)` 保护负索引，但**忽略了空树 `root == nullptr`**，直接 `root->val` 触发段错误 | [12_757309872_Runtime_Error.cpp](history/12_757309872_Runtime_Error.cpp) |
| **13** | `757310144` | ✅ **Accepted** | 22:01:06 | **补上 `if (root == nullptr) return result;`，所有边界完美闭合，0ms 击败 100% 登顶！**🎉 | [13_757310144_Accepted.cpp](history/13_757310144_Accepted.cpp) |

---

## 3. 错因深层剖析与三大核心顿悟

### 顿悟一：二叉树指针防崩法则——“解引用前必判空”
在提交 12 中引发崩溃的致命代码：
```cpp
list.push_back(root);
result.push_back(list[0]->val); // ❌ 如果 root 是 nullptr，这里直接段错误崩溃！
```
- **血泪教训**：二叉树所有题目的第 1 行代码，养成肌肉记忆：
  ```cpp
  if (!root) return {};
  ```
  永远不要对未经判空的指针做 `->` 解引用操作。

---

### 顿悟二：分层收集的“负索引陷阱”
在提交 10 中：
```cpp
for (int i = 0; i < list.size(); i++) {
    if (list[i]->left) { temp.push_back(list[i]->left); point++; }
    if (list[i]->right) { temp.push_back(list[i]->right); point++; }
}
result.push_back(temp[point - 1]->val); // ❌ 如果整层都是叶子节点，point=0，直接访问 temp[-1] 崩掉！
```
- **你的顿悟修复**：在提交 12 中加了 `if (point)`，只有当这层确实有节点生成时才去取末尾，非常精准！
- **STL 更优雅写法**：直接利用容器的 `temp.back()`，配合 `if (!temp.empty())`，不需要自己手动维护一个容易算错的 `point`。

---

### 顿悟三：二叉树 BFS 的两大流派（双缓冲 vs 单队列）

在这道题里，你自主推导出的解法是 **“双缓冲 Vector 轮替（Double Buffer）”**：
- `list` 存当前层；
- `temp` 收集下一层；
- 换层时 `list = temp`。
这种解法非常直观，而且在现代编译器优化下直接跑到了 **0 ms**！

与此对应的工业级标准写法是 **“单队列大小固定法（Single Queue with Level Size）”**：
```cpp
queue<TreeNode*> q;
q.push(root);
while (!q.empty()) {
    int level_size = q.size(); // 1. 锁死当前层的节点数！
    for (int i = 0; i < level_size; ++i) {
        TreeNode* node = q.front(); q.pop();
        if (i == level_size - 1) result.push_back(node->val); // 当前层最后一个就是右视图！
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}
```
**单队列的妙处**：利用 `level_size = q.size()` 一次性确定当前层有多少个节点，不需要开第二个 `temp` 数组，代码更加内敛。

---

## 4. 标杆最优解（双解法源码）

- **代码文件**：[solution.cpp](solution.cpp)

### 解法一：标准单队列层序遍历（推荐，工业级规范）
```cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (!root) return result; // 1. 空树特判守卫

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int level_size = q.size(); // 锁定当前层大小

            for (int i = 0; i < level_size; ++i) {
                TreeNode* node = q.front();
                q.pop();

                // 当前层的最后一个节点就是右侧视线落点
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
```

### 复杂度分析
- **时间复杂度**：$O(N)$，每个节点进出队列一次。
- **空间复杂度**：$O(D)$，其中 $D$ 是二叉树的最大宽度（最底层节点数，最多为 $N/2$）。
