# [26. Remove Duplicates from Sorted Array] 删除有序数组中的重复项

- **力扣链接**：[26. 删除有序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/?envType=study-plan-v2&envId=top-interview-150)
- **所属专题**：面试经典 150 题 - 数组 / 字符串
- **难度**：🟢 简单
- **做题时间**：2026-10-27 15:27 ~ 15:30（3 分钟内极速迭代 6 次提交并登顶）
- **掌握状态**：🟢 一次通过（快慢指针迁移成功，彻底理清下标与个数的偏移）
- **历史提交记录目录**：[history/](history/)

---

## 1. 题目大意与核心考点

- **一句话题意**：给你一个**升序排列**的数组 `nums`，请你**原地**删除重复出现的元素，使每个元素只出现一次，返回删除后数组的新长度 $k$。
- **评测契约**：
  - 评测只检查 `nums` 的前 $k$ 个元素，超出 $k$ 的尾部元素是什么无需关心。
  - 空间复杂度必须是 $O(1)$，不可借助额外哈希表或数组。
- **核心考点**：有序性质的利用、快慢双指针模型、循环不变量的区间定义。

---

## 2. 真实提交迭代轨迹（3 分钟高能复盘）

你从 15:27:59 开始提交，仅用了不到 3 分钟就完成了从**语法纠偏、逻辑修复到边界校准**的全部演进：

| 提交序号 | 提交编号 | 判题状态 | 提交时间 | 核心代码特征与错因剖析 | 源码切片链接 |
| :---: | :---: | :---: | :---: | :--- | :---: |
| **01** | `757217281` | ❌ Compile Error | 15:27:59 | 中文全角标点（`，` `；`）+ 漏写 `return` + 逻辑笔误 `nums[slow] == fast`（把值与下标混比） | [01_757217281_Compile_Error.cpp](history/01_757217281_Compile_Error.cpp) |
| **02** | `757217367` | ❌ Compile Error | 15:28:19 | 修正了英文逗号 `,`，补齐了 `return slow;`，但第 1 行末尾仍遗留了中文分号 `；` | [02_757217367_Compile_Error.cpp](history/02_757217367_Compile_Error.cpp) |
| **03** | `757217400` | ❌ Wrong Answer | 15:28:25 | 6 秒内换掉全角分号，编译通过！但此时仍是 `nums[slow] == fast`，导致逻辑错判 | [03_757217400_Wrong_Answer.cpp](history/03_757217400_Wrong_Answer.cpp) |
| **04** | `757217658` | ❌ Wrong Answer | 15:29:15 | 纠正为 `nums[slow] == nums[fast]`！但返回了 `return slow;`（漏掉了下标与长度的 +1 偏移） | [04_757217658_Wrong_Answer.cpp](history/04_757217658_Wrong_Answer.cpp) |
| **05** | `757217917` | ❌ Wrong Answer | 15:30:09 | 误尝试改为 `return fast;`，此时 `fast` 已遍历到末尾，返回了原数组全长 | [05_757217917_Wrong_Answer.cpp](history/05_757217917_Wrong_Answer.cpp) |
| **06** | `757218026` | ✅ **Accepted** | 15:30:37 | **顿悟出长度与下标关系**：改为 `return slow + 1;`，**0ms 击败 100% 通过！**🎉 | [06_757218026_Accepted.cpp](history/06_757218026_Accepted.cpp) |
| **07** | `757224657` | ✅ **Accepted** | 15:54:16 | 间隔半小时后的稳固复测提交，保持 AC！ | [07_757224657_Accepted.cpp](history/07_757224657_Accepted.cpp) |

---

## 3. 错因剖析与认知跃迁

### 认知卡点 1：中文输入法全角符号的隐蔽坑
```cpp
int slow = 0， fast = 1； // ❌ 中文逗号与分号，C++ 编译器报错 stray \357 等
```
- **启示**：在力扣网页端刷题时，中英文输入法切换如果不及时，容易引入中文字符；写代码前养成检查当前输入法状态的直觉。

---

### 认知卡点 2：元素值（Value）与下标（Index）的张冠李戴
在第 1 ~ 3 次提交中写的是：
```cpp
if (nums[slow] == fast) // ❌ 用 nums[slow] 的元素值去和 fast 的下标编号比较！
```
- **错因分析**：直觉上想表达“检查当前元素是否与下一个元素相等”，但手快把右边的 `nums[fast]` 漏写成了下标 `fast`。
- **修正**：`if (nums[slow] == nums[fast])`。

---

### 认知卡点 3：第 26 题 vs 第 27 题，`slow` 指针的语义差异（极度重要！）

很多同学刷完 27 题再来做 26 题，都会在最后 `return` 是不是 `+1` 上栽跟头：

| 题目 | slow 指针初始值 | slow 指针在循环中的语义 | 循环结束时有效元素个数 |
| :--- | :---: | :--- | :---: |
| **第 27 题（移除元素）** | `slow = 0` | 指向**下一个待写入的空位**（开区间末端） | 直接就是 **`slow`** |
| **第 26 题（有序去重）** | `slow = 0` | 指向**当前已确定的最后一个独立元素**（闭区间末端） | 是 **`slow + 1`**（下标从0起） |

- 在第 26 题中，第 0 个元素 `nums[0]` 本身一定是唯一且合法的，所以 `slow` 从 0 开始驻守。
- 只有当 `fast` 探路发现了不一样的数时，才执行：
  ```cpp
  nums[slow + 1] = nums[fast];
  slow++;
  ```
- 因此在任何时刻，`nums[0 .. slow]` 这整段都是去重后的有效序列。
- 既然下标是 `0 ~ slow`，那么总元素个数自然是 **`slow + 1`**！

---

## 4. 标杆最优解

- **代码文件**：[solution.cpp](solution.cpp)

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int slow = 0; // slow 指向当前已确定的最后一个独立元素
        int fast = 1; // fast 负责向前探路找寻不同的新元素

        while (fast < nums.size()) {
            if (nums[slow] == nums[fast]) {
                fast++; // 重复则跳过
            } else {
                nums[slow + 1] = nums[fast]; // 发现新数，入库
                slow++;
                fast++;
            }
        }

        // 下标为 [0..slow]，总个数为 slow + 1
        return slow + 1;
    }
};
```

### 复杂度分析
- **时间复杂度**：$O(N)$，`fast` 指针线性扫过数组一次。
- **空间复杂度**：$O(1)$，纯原地操作，无需额外内存。
