# [45. Jump Game II] 跳跃游戏 II

- **力扣链接**：[45. 跳跃游戏 II](https://leetcode.cn/problems/jump-game-ii/)
- **所属专题**：面试经典 150 题 - 数组 / 字符串 (Array / String)
- **难度**：🟡 中等
- **做题时间**：2026-10-30 12:20 ~ 12:30（共 10 次提交）
- **最终成绩**：✅ Accepted | 运行时间: **55 ms**（击败 13.68%） | 内存: **20.3 MB**（击败 39.74%）
- **掌握状态**：🟡 **踩坑修正（逆向自底向上原地 DP 攻克通过，后续可二刷升级正向双边界贪心 $O(N)$ 0ms 标杆）**
- **历史提交记录目录**：[history/](history/)
- **题解代码**：[solution.cpp](solution.cpp)

---

## 1. 题目大意与约束

- **一句话题意**：给定一个长度为 $n$ 的 0 索引整数数组 `nums`，初始位置为 `nums[0]`。每个元素 `nums[i]` 表示从索引 `i` 向前跳转的最大长度。返回到达 `nums[n - 1]` 的最小跳跃次数。
- **核心约束与测试特性**：
  - $1 \le nums.length \le 10^4$
  - $0 \le nums[i] \le 1000$
  - 生成的测试用例必定可以到达 `nums[n - 1]`
  - 边界特例：$n = 1$（起手就在终点），跳跃次数为 0，需先验防御

---

## 2. 真实提交迭代轨迹（全记录）

本题在 10 分钟内记录了 10 次高密度的实战调试，真实呈现了从自底向上原地 DP 踩坑、越界内存崩溃 (RE)、Off-by-one 补偿陷阱到最终通过的完整心路：

| 提交序号 | 提交编号 | 判题状态 | 提交时间 | 运行用时 | 通过用例 | 核心特征与错因剖析 | 源码切片链接 |
| :---: | :---: | :---: | :---: | :---: | :---: | :--- | :---: |
| **01** | `757745187` | ❌ Wrong Answer | 12:20:02 | N/A | 逆向 DP 状态覆盖混乱：$i$ 从 $p$ 开始且 $j$ 从 0 开始，把自身当成跳跃目标且漏加步数 (+1) | [01_757745187_Wrong_Answer.cpp](history/01_757745187_Wrong_Answer.cpp) |
| **02** | `757745206` | ❌ Wrong Answer | 12:20:16 | N/A | 补加 +1，但单元素直接执行，返回 nums[0]-1 出现负值与偏差 | [02_757745206_Wrong_Answer.cpp](history/02_757745206_Wrong_Answer.cpp) |
| **03** | `757745384` | ❌ Wrong Answer | 12:22:37 | N/A | 调整初始极值 min=1000，但内层 j 依然从 0 开始导致自身未更新数据干扰计算 | [03_757745384_Wrong_Answer.cpp](history/03_757745384_Wrong_Answer.cpp) |
| **04** | `757745425` | ❌ Wrong Answer | 12:23:09 | N/A | 补上 `if (!p) return 0;` 单元素特判，但内层循环未做数组越界防御 | [04_757745425_Wrong_Answer.cpp](history/04_757745425_Wrong_Answer.cpp) |
| **05** | `757745668` | ❌ Wrong Answer | 12:25:56 | N/A | 增加 `if(nums[i])` 过滤 0 步长，但步长范围与内层循环仍有偏差 | [05_757745668_Wrong_Answer.cpp](history/05_757745668_Wrong_Answer.cpp) |
| **06** | `757745872` | ❌ Runtime Error | 12:28:37 | N/A | 步长判断改用 `j <= nums[i]`，当 $i+j \ge n$ 时触发越界内存崩溃 (Runtime Error) | [06_757745872_Runtime_Error.cpp](history/06_757745872_Runtime_Error.cpp) |
| **07** | `757745917` | ❌ Wrong Answer | 12:29:20 | N/A | 加上 `i+j < nums.size()` 越界防御，通过数升至 21，但 $j$ 从 0 开始使得 nums[i] 自身数值干扰 min 计算 | [07_757745917_Wrong_Answer.cpp](history/07_757745917_Wrong_Answer.cpp) |
| **08** | `757745940` | ❌ Wrong Answer | 12:29:42 | N/A | 重大突破：调整边界 $i$ 从 $p-1$ 开始、$j$ 从 1 开始；但残留 `return nums[0]-1;` 导致答案偏小 1 | [08_757745940_Wrong_Answer.cpp](history/08_757745940_Wrong_Answer.cpp) |
| **09** | `757746008` | ❌ Wrong Answer | 12:30:28 | N/A | 调大 min 为 10000 防溢出截断，仍未修正 `return nums[0]-1;` | [09_757746008_Wrong_Answer.cpp](history/09_757746008_Wrong_Answer.cpp) |
| **10** | `757746011` | ✅ **Accepted** | 12:30:34 | 55 ms | 改回纯正的 `return nums[0];`，**逆向原地 DP 解法 111/111 全用例通过 AC**！🎉 | [10_757746011_Accepted.cpp](history/10_757746011_Accepted.cpp) |

---

## 3. 错因深层复盘与认知跃迁

### 1. 原地复用数组 DP 的“状态污染”陷阱
- **陷阱**：在把 `nums[i]` 复用为 $dp[i]$（从索引 $i$ 到达终点所需的最小跳跃步数）时，如果 $j$ 从 0 开始循环：
  `min = std::min(min, nums[i + 0] + 1);`
  此时 `nums[i]` 存放的还是原始的最大跳跃跨度，而不是 DP 状态值！将“跳跃能力”和“历史步数”混用造成灾难。
- **破局**：步长必须严格为正整数（$j \ge 1$），且当前点 $i$ 的最优步数只能由已经计算好的后续位置 $i+j$ 转移而来：
  $$dp[i] = 1 + \min_{1 \le j \le nums[i],\, i+j < n} dp[i+j]$$

### 2. 数组越界防御的必要性
- 虽然测试用例保证能到达终点，但某个位置的跳跃能力 `nums[i]` 可能极大（例如在下标 2 处跳 100 步直接飞出数组）。
- `for (int j = 1; j <= nums[i] && i + j < nums.size(); j++)` 中的 `i + j < nums.size()` 必须作为短路保护条件，否则立刻触发越界访问内存崩溃 (RE)。

### 3. Off-by-one 补偿补丁的心智负担
- 前期因为 $j=0$ 多算了一次自跳，写了 `return nums[0] - 1;` 试图通过外层补丁掩盖内层缺陷；
- 当内层逻辑修正为 $j \in [1, nums[i]]$ 后，必须果断摘除补偿补丁，回归客观的 `return nums[0];`。

---

## 4. 标杆题解与进阶双模型对比

### 模型 A：逆向自底向上原地动态规划（你的 AC 解法）
- **核心源码**：[solution.cpp](solution.cpp)
- **时间复杂度**：最坏情况 $O(N^2)$（当跳跃步数较大时需多次内层扫描）。在力扣 111 个测试用例下耗时 55 ms。
- **空间复杂度**：严格 $O(1)$，直接复用原数组存储状态，零额外内存开销！

### 模型 B：正向贪心双边界法（电量跃迁模型 —— 0ms 终极标杆）
- **核心洞察**：
  我们并不关心具体每一步跳到哪个格子上，只关心**当前这一跳的最远覆盖范围 `curEnd`**。
  - 在当前跳跃范围 $[\dots, curEnd]$ 内遍历时，实时记录下一跳能达到的全局最远位置 `maxReach = max(maxReach, i + nums[i])`。
  - 一旦指针遍历到了当前跳跃的边界 `curEnd`（说明这一跳的能量耗尽，必须再跳一次）：
    - `steps++`
    - `curEnd = maxReach`
    - 若 `curEnd >= n - 1`，可提前终止剪枝！
- **C++ 标杆代码**：
  ```cpp
  class Solution {
  public:
      int jump(vector<int>& nums) {
          int n = nums.size();
          if (n <= 1) return 0;
          int steps = 0, curEnd = 0, maxReach = 0;
          for (int i = 0; i < n - 1; ++i) {
              maxReach = max(maxReach, i + nums[i]);
              if (i == curEnd) {
                  steps++;
                  curEnd = maxReach;
                  if (curEnd >= n - 1) break;
              }
          }
          return steps;
      }
  };
  ```
- **复杂度对比**：单次线性扫描 $O(N)$，空间严格 $O(1)$，**0 ms 击败 100%**！

---

## 5. 避坑 Checklist
- [ ] $n = 1$ 起点即终点是否进行了先验特判返回 0？
- [ ] 内层循环探索是否添加了 `i + j < nums.size()` 越界保护？
- [ ] 正向贪心循环上限是否停在 $n-2$（到达最后一个元素前无需再次跳跃）？
- **一句话题意**：跳跃游戏 II

---

## 2. 真实提交迭代轨迹

| 提交序号 | 提交编号 | 判题状态 | 提交时间 | 核心特征与评价 | 源码切片链接 |
| :---: | :---: | :---: | :---: | :--- | :---: |
| **01** | `757745187` | ❌ Wrong Answer | 12:20:02 | 力扣历史提交记录 | [01_757745187_Wrong_Answer.cpp](history/01_757745187_Wrong_Answer.cpp) |
| **02** | `757745206` | ❌ Wrong Answer | 12:20:16 | 力扣历史提交记录 | [02_757745206_Wrong_Answer.cpp](history/02_757745206_Wrong_Answer.cpp) |
| **03** | `757745384` | ❌ Wrong Answer | 12:22:37 | 力扣历史提交记录 | [03_757745384_Wrong_Answer.cpp](history/03_757745384_Wrong_Answer.cpp) |
| **04** | `757745425` | ❌ Wrong Answer | 12:23:09 | 力扣历史提交记录 | [04_757745425_Wrong_Answer.cpp](history/04_757745425_Wrong_Answer.cpp) |
| **05** | `757745668` | ❌ Wrong Answer | 12:25:56 | 力扣历史提交记录 | [05_757745668_Wrong_Answer.cpp](history/05_757745668_Wrong_Answer.cpp) |
| **06** | `757745872` | ❌ Runtime Error | 12:28:37 | 力扣历史提交记录 | [06_757745872_Runtime_Error.cpp](history/06_757745872_Runtime_Error.cpp) |
| **07** | `757745917` | ❌ Wrong Answer | 12:29:20 | 力扣历史提交记录 | [07_757745917_Wrong_Answer.cpp](history/07_757745917_Wrong_Answer.cpp) |
| **08** | `757745940` | ❌ Wrong Answer | 12:29:42 | 力扣历史提交记录 | [08_757745940_Wrong_Answer.cpp](history/08_757745940_Wrong_Answer.cpp) |
| **09** | `757746008` | ❌ Wrong Answer | 12:30:28 | 力扣历史提交记录 | [09_757746008_Wrong_Answer.cpp](history/09_757746008_Wrong_Answer.cpp) |
| **10** | `757746011` | ✅ **Accepted** | 12:30:34 | 力扣历史提交记录 | [10_757746011_Accepted.cpp](history/10_757746011_Accepted.cpp) |

---

## 3. 标杆最优解

代码详见 [solution.cpp](solution.cpp)。
