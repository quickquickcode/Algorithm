# [27. Remove Element] 移除元素

- **力扣链接**：[27. 移除元素](https://leetcode.cn/problems/remove-element/?envType=study-plan-v2&envId=top-interview-150)
- **所属专题**：面试经典 150 题 - 数组 / 字符串
- **难度**：🟢 简单
- **做题时间**：2026-10-27
- **首次耗时**：约 30 分钟
- **掌握状态**：🟡 踩坑修正（需重点掌握快慢指针模型）

---

## 1. 题目大意与核心约束

- **一句话题意**：给你一个数组 `nums` 和一个值 `val`，需要**原地**移除所有数值等于 `val` 的元素，并返回移除后数组的新长度 $k$。
- **评测规范**：
  - 评测系统只验证 `nums` 的前 $k$ 个元素，超出 $k$ 的剩余元素是什么无需关心。
  - **不需要调用 `resize()` 改变物理数组大小**。
  - 元素的顺序可以改变。
- **关键约束**：
  - $0 \le nums.length \le 100$
  - $0 \le nums[i] \le 50$
  - 边界极端情况：空数组、数组中全部都是 `val`、数组中没有一个 `val`。

---

## 2. 初见直觉与思维瓶颈（心路历程）

- **直觉思路**：“把等于 `val` 的元素换到数组末尾去”。
  - 既然要把等于 `val` 的扔后面，就用左指针找 `val`，右指针找非 `val`，找到一对就做一次 `swap`。
- **思维卡点**：
  - 用了两个内层 `while` 来寻找位置，却忽略了**数组边界防护**。
  - 状态变量命名混乱（引入了无意义的 `t` 和 `sum`），误以为需要自己算删除了多少个再用 `resize` 截断。
  - 混淆了“返回新数组长度”与“返回被移除元素数量”。

---

## 3. 中途错误代码与迭代轨迹（踩坑博物馆）

### 尝试 1：左右指针交换 + 内层无界 + 统计逻辑混乱
- **错误代码文件**：[solution_wrong.cpp](solution_wrong.cpp)
- **提交结果**：运行时错误 (Segmentation Fault / AddressSanitizer Heap-buffer-overflow)
```cpp
int x = 0, y = nums.size() - 1;
int sum = 0;
while (x < y) {
    int t = 0;
    while (nums[x] != val) { x++; } // ❌ 越界大坑
    while (nums[y] == val) { y--; } // ❌ 下溢大坑
    t++;
    if (x < y) {
        int temp = nums[y];
        nums[y] = nums[x];
        nums[x] = temp;
        sum += t;
    }
}
nums.resize(nums.size() - sum);
return sum;
```
- **五大致命问题剖析**：
  1. **内层 `while` 无边界检查（必炸）**：
     - 若 `nums` 中没有 `val`，`x` 会一路递增超过 `nums.size()`，访问未分配内存导致崩溃。
     - 若 `nums` 全部是 `val`，`y` 会一路减至 `-1`，访问 `nums[-1]` 导致下溢崩溃。
  2. **`sum` 累加逻辑完全荒谬**：
     - `t` 只是每轮循环自增 1，然后累加到 `sum`，根本不是等于 `val` 的实际个数。
  3. **交换后未推进指针**：
     - 执行 `temp` 交换后，`x` 和 `y` 依然停留在原位，下一轮完全依赖内层循环推进，容易陷入边界失效或死循环。
  4. **外层条件 `while (x < y)` 漏判相遇点**：
     - 当 `x == y` 时直接跳出循环，相遇位置上的那个元素到底是 `val` 还是有效元素完全没被检查（例如输入 `[2]`, `val=2` 时，直接返回错误）。
  5. **画蛇添足的 `resize()` 与返回值错误**：
     - 题目只要求返回有效长度 $k$，结果却返回了被移除计数 `sum`，还试图用错误的 `sum` 去截断数组。

---

## 4. 认知跃迁（Aha Moment）

> 💡 **核心破局点：从“交换思维”转向“收集/覆盖思维”！**

1. **不需要交换，只需要“覆盖”**：
   - 题目根本不在意被丢弃的元素最后落在哪，我们根本不需要把垃圾“小心翼翼地交换到后面”，直接拿有效数据**覆盖**掉垃圾即可！
2. **快慢指针：最坚固的心智模型**：
   - 快指针 `fast` 无脑向前探路：如果是垃圾（等于 `val`），不管它，继续走；如果不是垃圾，立刻搬给慢指针 `slow`，然后 `slow++`。
   - 彻底避免内层 `while`，彻底消除一切越界可能。
3. **对撞覆盖（优化版）**：
   - 如果遇到等于 `val` 的位置，直接把末尾 `nums[right]` 拿来填坑（`nums[left] = nums[right]; right--;`）。
   - 此时 `left` 不要移动，因为移过来的元素可能也是 `val`，留在原地下一轮继续校验。

---

## 5. 标杆最优解

### 解法一：快慢指针法（代码最简洁、最稳健，首选）
- **代码文件**：[solution_fast_slow.cpp](solution_fast_slow.cpp)
```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < nums.size(); ++fast) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow++;
            }
        }
        return slow;
    }
};
```
- **时空复杂度**：时间 $O(N)$，空间 $O(1)$。

---

### 解法二：对撞覆盖双指针（移动次数最少）
- **代码文件**：[solution_two_pointers.cpp](solution_two_pointers.cpp)
```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            if (nums[left] == val) {
                nums[left] = nums[right];
                right--;
            } else {
                left++;
            }
        }
        return left;
    }
};
```
- **时空复杂度**：时间 $O(N)$，空间 $O(1)$。在要删除的元素极少时（如 1000 个数里只有 1 个等于 `val`），快慢指针要做 999 次自我赋值，而对撞指针只需要 1 次覆盖。

---

## 6. 避坑 Checklist

- [ ] 是否在任何内层指针移动 `while` 里都强制加上了 `idx < size` 或 `idx >= 0`？
- [ ] 题目返回值是“有效长度”还是“删除数量”？（本题是新长度）。
- [ ] 是否不必要地调用了 `resize()`？（绝大多数题目无需调用）。
- [ ] 对撞双指针是否使用了 `left <= right` 避免漏掉中间单元素？
