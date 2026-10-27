# [42. Trapping Rain Water] 接雨水

- **力扣链接**：[42. 接雨水](https://leetcode.cn/problems/trapping-rain-water/)
- **所属专题**：面试经典 150 题 - 数组 / 双指针
- **难度**：🔴 **困难 (Hard)** —— 力扣最负盛名的经典题之一
- **做题时间**：2026-10-27 22:10 ~ 22:11（历时不到 1 分钟，3 次提交极速攻克 Hard 题）
- **最终成绩**：✅ Accepted | 运行时间: **0 ms**（击败 100%） | 内存: 25.3 MB
- **掌握状态**：🟢 一次攻克（最高峰拆分法，以极度简练的逻辑秒杀 Hard）
- **历史提交记录目录**：[history/](history/)

---

## 1. 题目大意与数学模型

- **一句话题意**：给定 $n$ 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子下雨之后能接多少雨水。
- **物理与数学本质**：
  每一个坐标 $i$ 能接多少水，仅取决于它左右两侧的最高柱子（木桶理论短板原则）：
  $$\text{water}[i] = \max(0, \min(\text{max\_left}[i], \text{max\_right}[i]) - \text{height}[i])$$

---

## 2. 真实提交迭代轨迹（1 分钟拿下 Hard）

| 提交序号 | 提交编号 | 判题状态 | 提交时间 | 核心特征与错因剖析 | 源码切片链接 |
| :---: | :---: | :---: | :---: | :--- | :---: |
| **01** | `757312053` | ❌ Compile Error | 22:10:21 | 结构完全正确！仅因末尾漏写了 `return sum;` 导致编译失败 | [01_757312053_Compile_Error.cpp](history/01_757312053_Compile_Error.cpp) |
| **02** | `757312118` | ❌ Wrong Answer | 22:10:39 | 补上 `return sum;`，但**右向左扫描前忘记重置 `max = -1`**，导致右侧扫描继承了左侧的极大值 | [02_757312118_Wrong_Answer.cpp](history/02_757312118_Wrong_Answer.cpp) |
| **03** | `757312215` | ✅ **Accepted** | 22:11:08 | **29 秒后补上 `max = -1;` 重置，0ms 击败 100% 登顶 Hard！**🎉 | [03_757312215_Accepted.cpp](history/03_757312215_Accepted.cpp) |

---

## 3. 思维破局：为什么“最高峰拆分法”具有降维神效？

很多同学做接雨水都会陷入单调栈或前缀数组（$O(N)$ 额外空间）的复杂推导中，而你采用的**最高峰拆分法（Peak Partitioning）**具有极高的数学美感：

### 核心灵感：寻找世界屋脊（全局最高点 $P$）
1. 整个柱状图一定存在一个全局最高点 $P$（`height[P]` 最大）。
2. **在最高峰 $P$ 的左侧（$i < P$）**：
   - 它的右边永远有一个“世界屋脊” $P$ 挡着（$\text{max\_right} \ge \text{height}[P] \ge \text{max\_left}$）。
   - 所以在左侧，木桶的短板**必然是左侧最高点 `max_left`**，根本不需要看右边！
3. **在最高峰 $P$ 的右侧（$i > P$）**：
   - 同理，它的左边永远有世界屋脊 $P$ 挡着，短板**必然是右侧最高点 `max_right`**！
4. **结论**：
   以最高峰为界，把原本复杂的双向约束彻底解耦成了**两次独立的前缀最大值扫描**！
   时间 $O(N)$，额外空间 $O(1)$，代码没有任何复杂的栈或双指针碰撞，堪称力扣接雨水最直观、最好写的优雅神解。

---

## 4. 标杆最优解

- **代码文件**：[solution.cpp](solution.cpp)

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;

        // 1. 寻找世界屋脊（全局最高柱子）
        int p = 0, max_val = -1;
        for (int i = 0; i < height.size(); i++) {
            if (height[i] > max_val) {
                max_val = height[i];
                p = i;
            }
        }

        int sum = 0;

        // 2. 左半区：只需看左侧短板
        max_val = -1;
        for (int i = 0; i < p; i++) {
            if (height[i] > max_val) max_val = height[i];
            else sum += max_val - height[i];
        }

        // 3. 右半区：只需看右侧短板（切记重置 max_val!）
        max_val = -1;
        for (int i = height.size() - 1; i > p; i--) {
            if (height[i] > max_val) max_val = height[i];
            else sum += max_val - height[i];
        }

        return sum;
    }
};
```
