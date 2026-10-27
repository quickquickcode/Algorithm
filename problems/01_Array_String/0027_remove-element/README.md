# [27. Remove Element] 移除元素

- **力扣链接**：[27. 移除元素](https://leetcode.cn/problems/remove-element/?envType=study-plan-v2&envId=top-interview-150)
- **所属专题**：面试经典 150 题 - 数组 / 字符串
- **难度**：🟢 简单
- **做题时间**：2026-10-27 15:04 ~ 15:18（历时 14 分钟，共 7 次提交）
- **掌握状态**：🟢 一次通过（经历完整真实迭代并最终掌握快慢指针）
- **历史提交记录目录**：[history/](history/)

---

## 1. 题目大意与评测契约

- **一句话题意**：给你一个数组 `nums` 和一个值 `val`，需要**原地**移除所有数值等于 `val` 的元素，并返回移除后数组的新长度 $k$。
- **力扣评测契约**：
  - 评测系统只验证 `nums` 的前 $k$ 个元素，超出 $k$ 的尾部元素是什么无需关心。
  - **不需要调用 `resize()` 改变物理数组大小**。
  - 元素的顺序可以改变。

---

## 2. 真实提交迭代轨迹（全记录）

本题在 14 分钟内留下了 7 次极其真实的力扣真实提交历史，完整展现了**从“对撞指针踩坑”到“快慢指针顿悟通过”**的思维演进过程：

| 提交序号 | 提交编号 | 判题状态 | 提交时间 | 核心代码特征与错因剖析 | 源码切片链接 |
| :---: | :---: | :---: | :---: | :--- | :---: |
| **01** | `757210894` | ❌ Wrong Answer | 15:04:53 | 内层 `while` 前移 + 手动赋 0（`nums[right]=0`）；返回 `times`；`while(left < right)` 漏相遇点 | [01_757210894_Wrong_Answer.cpp](history/01_757210894_Wrong_Answer.cpp) |
| **02** | `757211065` | ❌ Wrong Answer | 15:05:31 | 删除了多余的 `nums[right]=0`，但外层仍是 `left < right`，相遇点漏判 | [02_757211065_Wrong_Answer.cpp](history/02_757211065_Wrong_Answer.cpp) |
| **03** | `757211534` | ❌ Wrong Answer | 15:07:17 | 优化为 `if-else` 分支结构（`!= val` 则 `left++`，否则覆盖），但仍受制于 `<` 和 `times` 返回值 | [03_757211534_Wrong_Answer.cpp](history/03_757211534_Wrong_Answer.cpp) |
| **04** | `757212016` | ❌ Wrong Answer | 15:09:01 | **致命笔误**：漏写了 `else`，导致第二块花括号无条件每轮执行强行覆盖；返回 `nums.size() - times` | [04_757212016_Wrong_Answer.cpp](history/04_757212016_Wrong_Answer.cpp) |
| **05** | `757214383` | ❌ Compile Error | 15:17:44 | **思维升级**：果断切换到「快慢双指针」！逻辑已完全正确，但漏写了 `return` 语句导致编译错误 | [05_757214383_Compile_Error.cpp](history/05_757214383_Compile_Error.cpp) |
| **06** | `757214452` | ❌ Wrong Answer | 15:17:56 | 12 秒后为了快速修编译错误，随手补了 `return 0;` | [06_757214452_Wrong_Answer.cpp](history/06_757214452_Wrong_Answer.cpp) |
| **07** | `757214526` | ✅ **Accepted** | 15:18:12 | 16 秒后改回正确的 `return slow;`，**0ms 一遍击败 100% 通过**！🎉 | [07_757214526_Accepted.cpp](history/07_757214526_Accepted.cpp) |

---

## 3. 错因深层复盘与认知跃迁

### 核心卡点 1：对撞双指针为什么容易写错？
1. **漏写 `else` 的隐蔽灾难**：
   在提交 `04` 中：
   ```cpp
   if (nums[left] != val) { left++; times++; }
   { nums[left] = nums[right]; right--; } // 漏写 else！变成每轮无条件执行
   ```
   导致一旦当前元素合法跳过了，紧接着立刻把下一个未检查的元素给抹杀掉了。
2. **`while (left < right)` 漏判单元素**：
   当 `nums = [2], val = 2` 时，$0 < 0$ 为假，循环根本不进，相遇点的元素完全脱靶。

---

### 核心卡点 2：为什么快慢指针是解决此题的最优心智模型？
从对撞指针切换到快慢指针（提交 `05 ~ 07`）是本次刷题的**最大顿悟点**：
- **快指针 `fast`（探路者）**：无脑遍历数组中的每一个坑位。
- **慢指针 `slow`（有效坑位守护者）**：遇到垃圾（等于 `val`）不理会，遇到合法数据才接过来放到 `nums[slow]` 并自增。
- **天然无越界**：只向前单向推进，没有任何回退、交换或相遇点判断，复杂度稳定 $O(N)$，空间 $O(1)$。

---

## 4. 标杆最优解（终极 AC 代码）

- **对应提交**：`757214526`
- **代码文件**：[history/07_757214526_Accepted.cpp](history/07_757214526_Accepted.cpp)

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0, fast = 0;
        while (fast < nums.size()) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        return slow; // slow 即为新数组的长度
    }
};
```

### 复杂度分析
- **时间复杂度**：$O(N)$，`fast` 指针遍历数组一次。
- **空间复杂度**：$O(1)$，纯原地修改，仅占用常数级内存。
