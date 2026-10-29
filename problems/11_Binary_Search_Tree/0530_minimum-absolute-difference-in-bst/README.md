# [530. Minimum Absolute Difference in BST] 二叉搜索树的最小绝对差

- **力扣链接**：[530. 二叉搜索树的最小绝对差](https://leetcode.cn/problems/minimum-absolute-difference-in-bst/)
- **所属专题**：面试经典 150 题 - 二叉搜索树 (Binary Search Tree)
- **难度**：🟢 简单（BST 特性高频考察题）
- **做题时间**：2026-10-29 15:38
- **当前状态**：🟡 踩坑调试中（提交 `757606598` 报 Wrong Answer，在用例 `[100000, 0]` 上暴露出致命运算与遍历认知盲区）
- **历史提交记录目录**：[history/](history/)
- **调试可执行入口**：[debug.cpp](debug.cpp)
- **标准题解源码**：[solution.cpp](solution.cpp)

---

## 1. 题目大意与核心特征

- **一句话题意**：给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两不同节点值之间的**最小绝对差**。
- **树的规模与约束**：
  - 树中节点数目在范围 $[2, 10^4]$ 内
  - $0 \le \text{Node.val} \le 10^5$
- **BST 的黄金数学本质**：
  > **二叉搜索树的【中序遍历】（左 $\rightarrow$ 根 $\rightarrow$ 右）必定是一个严格递增的有序序列！**
  > 在一个升序数组中，**最小差值必定发生在相邻两个元素之间**！绝不需要全局两两比较，也绝不能只比较直接父子！

---

## 2. 真实提交记录与卡点实录

| 提交序号 | 提交编号 | 判题状态 | 提交时间 | 核心特征与错因剖析 | 源码切片链接 |
| :---: | :---: | :---: | :---: | :--- | :---: |
| **01** | `757606598` | ❌ Wrong Answer | 15:38:22 | 1. 语法陷阱：`10^6` 算成异或运算得 12；<br>2. 算法漏洞：仅比较直接父子，错失跨层前驱后继。在用例 `[100000, 0]` 输出 12（预期 100000）。 | [01_757606598_Wrong_Answer.cpp](history/01_757606598_Wrong_Answer.cpp) |
| **02** | `757610552` | ❌ Compile Error | 15:53:03 | 尝试修复异或运算时误用了 Python 的乘方语法 `10**6`，导致 C++ 编译失败 | [02_757610552_Compile_Error.cpp](history/02_757610552_Compile_Error.cpp) |
| **03** | `757610627` | ❌ Wrong Answer | 15:53:23 | 将初始值修正为 `1000000` 消除语法错误，但算法本质仍局限于直接父子比较，依然无法通过跨层用例 | [03_757610627_Wrong_Answer.cpp](history/03_757610627_Wrong_Answer.cpp) |

---

## 3. 错因深层剖析：为什么会在用例 `[100000, 0]` 上翻车？

你的原始核心代码：
```cpp
int getMinimumDifference(TreeNode* root) {
    int min = 10^6; // ⚠️ 致命 Bug 1
    if (root->left == nullptr && root->right == nullptr) {
        return min;
    }
    if (root->left != nullptr) {
        min = std::min(root->val - root->left->val, min); // ⚠️ 算法缺陷 2
        min = std::min(min, getMinimumDifference(root->left));
    }
    if (root->right != nullptr) {
        min = std::min(root->right->val - root->val, min);
        min = std::min(min, getMinimumDifference(root->right));
    }
    return min;
}
```

### 致命陷阱 1：C++ 语法坑——`10^6` 绝对不是 $10^6$！
- 在数学与某些脚本语言（如 Python `**`）中表示乘方，但在 C/C++ 中：
  **`^` 是按位异或 (Bitwise XOR) 运算符！**
  $$10 \oplus 6 = (1010)_2 \oplus (0110)_2 = (1100)_2 = 12$$
- **执行过程复盘**：
  对于输入 `root->val = 100000`, `root->left->val = 0`:
  1. `min` 被初始化为 `10 ^ 6 = 12`；
  2. 计算 `root->val - root->left->val = 100000 - 0 = 100000`；
  3. 执行 `min = std::min(100000, min)`，也就是 `std::min(100000, 12)`；
  4. **`min` 被强行改写成了 `12`！**
  5. 递归进入左孩子 `root->left`（值为 0，是叶子节点），命中 `left == nullptr && right == nullptr`，直接返回 `min = 10^6 = 12`；
  6. 外层函数最终返回 `12`！
- **语法正解**：
  C++ 中表示大整数初始值，请使用：
  - `INT_MAX`（需引入 `<climits>`）；
  - `1000000` 或 `1e6`（`1e6` 类型为 `double`，赋值给 `int` 会隐式转换）；
  - 或者直接给全局/成员变量维护状态。

---

### 算法本质缺陷 2：局部父子比较不是 BST 的最小邻近距离！
即使你把 `10^6` 改成 `INT_MAX`，在 `[100000, 0]` 上碰巧能过，但面对复杂树时仍会遭遇大面积 WA！

#### 典型反例：`[236, 104, 701, null, 227, null, 911]`
```
       236
      /   \
    104   701
      \     \
      227   911
```
- **真实最小差值**：发生在 `236` 与其左子树的最右节点 `227` 之间：
  $$|236 - 227| = 9$$
- **你的代码检查了谁？**
  - 在 `236` 节点：只检查了直接左孩子 `104` ($236 - 104 = 132$) 和直接右孩子 `701` ($701 - 236 = 465$)；
  - 在 `104` 节点：只检查了其直接右孩子 `227` ($227 - 104 = 123$)；
  - 递归返回后，代码得到的最小值是 $123$，**彻底漏掉了跨层的 236 与 227 之间的差值 9**！

---

## 4. 认知跃迁：BST 的解题母模——「中序遍历升序序列」

任何有关二叉搜索树（BST）关于 **“最值、差值、第 K 大/小、众数、验证合法性”** 的问题，95% 都可以通过同一个思维钥匙解开：

```
二叉搜索树 (BST)  ──────中序遍历 (左-中-右)──────>  严格单调递增数组
```

在递增序列 $[a_0, a_1, a_2, \dots, a_n]$ 中：
- 最小绝对差一定出现在某对**相邻元素** $a_i - a_{i-1}$ 之间！
- 我们根本不需要把整棵树转存成数组，只需在递归遍历中维护一个指向前驱节点的指针 `prev` 即可实现 $O(1)$ 额外空间（不计递归栈）。

```cpp
class Solution {
private:
    int minDiff = INT_MAX;
    TreeNode* prev = nullptr; // 记录中序遍历序列中的前一个节点

    void inOrder(TreeNode* root) {
        if (!root) return;

        // 1. 递归左子树
        inOrder(root->left);

        // 2. 当前节点逻辑：与前驱节点比对差值
        if (prev != nullptr) {
            minDiff = std::min(minDiff, root->val - prev->val);
        }
        prev = root; // 前驱指针后移为当前节点

        // 3. 递归右子树
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
```

---

## 5. VS Code 一键单步调试指南

我们在工作区为你配置好了专属调试配置：

1. **源文件**：直接在 VS Code 中打开 [debug.cpp](debug.cpp)；
2. **打断点**：在 `debug.cpp` 的第 30 行（`int min = 10^6;`）或者第 97 行左侧行号旁点击打上红点断点；
3. **启动调试**：
   - 按键盘快捷键 `F5`；
   - 或点击 VS Code 左侧活动栏的 **“运行与调试 (Run and Debug)”** 图标，顶部下拉菜单选择：
     `🐛 调试 530: [100000, 0] (C/C++ LLDB)`
4. **单步观测**：
   - 按 `F10` 单步步过，按 `F11` 单步跟入；
   - 在左侧 **“变量 (Variables)”** 窗口亲眼观察 `min` 变量被赋值为 `12`，以及后续 `std::min(100000, 12)` 是如何把结果锁死在 12 的！
