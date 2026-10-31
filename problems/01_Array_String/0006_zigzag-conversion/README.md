# [6. Zigzag Conversion] Z 字形变换

- **力扣链接**：[6. Z 字形变换](https://leetcode.cn/problems/zigzag-conversion/)
- **所属专题**：面试经典 150 题 - 数组 / 字符串 (Array / String)
- **难度**：🟡 中等
- **做题时间**：2026-10-31 17:22 ~ 17:44（共 14 次提交）
- **最终成绩**：✅ Accepted | 运行时间: **4 ms**（击败 64.82%） | 内存: **10.9 MB**（击败 78.50%）
- **掌握状态**：🟡 **踩坑修正（完整复盘 14 次迭代，最终 0ms 突破）**
- **历史提交记录目录**：[history/](history/)
- **题解代码**：[solution.cpp](solution.cpp)

---

## 1. 题目大意与约束

- **一句话题意**：将字符串 `s` 按照给定的行数 `numRows` 从上往下、从左到右排成 Z 字形（实为折线 V 形），随后逐行读取拼接成新的字符串。
- **核心契约与边界**：
  - 当 $numRows = 1$ 或 $numRows \ge s.length$ 时，形状退化为一条直线，必须直接返回 `s`。
  - 完整 V 字折线的一个周期跨度为 $T = 2 \times (numRows - 1)$。
  - 首行（$i = 0$）与末行（$i = numRows - 1$）每个周期内仅有 1 个字符；中间行（$0 < i < numRows - 1$）每个周期内包含 2 个字符（下行垂直点与斜上行对角点）。

---

## 2. 真实提交迭代轨迹（全记录）

本题经历了 14 次极其真实且宝贵的调试迭代。从最初的乘法语法失误、死循环、特判缺失，到敏锐洞察出“拐角自反射”现象，并在极度困惑时尝试通过 `s.pop_back()` 规避，直至最终彻底顿悟“跨越折返拐角”的数学本质，完整呈现了一段极具教学价值的心智成长轨迹：

| 提交序号 | 提交编号 | 判题状态 | 提交时间 | 核心特征与错因剖析 | 源码切片链接 |
| :---: | :---: | :---: | :---: | :--- | :---: |
| **01** | `757922279` | ❌ Compile Error | 17:22:30 | 语法错误：`2(n-1)` 缺失乘号 `*`，且未声明变量 `n` (Compile Error) | [01_757922279_Compile_Error.cpp](history/01_757922279_Compile_Error.cpp) |
| **02** | `757922323` | ❌ Compile Error | 17:22:45 | 语法修正：修正变量名为 `numRows`，但仍遗漏乘号 `2(numRows-1)` (Compile Error) | [02_757922323_Compile_Error.cpp](history/02_757922323_Compile_Error.cpp) |
| **03** | `757922345` | ❌ Time Limit Exceeded | 17:22:52 | 死循环超时：补全乘号 `2*(numRows-1)*(i+1)-j`，但在内部用了固定的 `i+1`，步长未动态推进引发死循环 (TLE) | [03_757922345_Time_Limit_Exceeded.cpp](history/03_757922345_Time_Limit_Exceeded.cpp) |
| **04** | `757922599` | ❌ Wrong Answer | 17:24:36 | 未特判单行：引入自增计数器 `times`，公式变为 `2*(numRows-1)*(times+1)-j`；未特判 `numRows=1` 致死循环 WA | [04_757922599_Wrong_Answer.cpp](history/04_757922599_Wrong_Answer.cpp) |
| **05** | `757922916` | ❌ Wrong Answer | 17:26:35 | 自对称停滞：增加 `if(numRows==1) return s;` 特判，通过 73/1158 用例；但在顶底行反射落到自身导致原地停滞 WA | [05_757922916_Wrong_Answer.cpp](history/05_757922916_Wrong_Answer.cpp) |
| **06** | `757923479` | ❌ Compile Error | 17:30:02 | 调试代码：尝试通过限制外层行循环为 `numRows-1` 并粘贴样例输出调试，出现语法错误 (Compile Error) | [06_757923479_Compile_Error.cpp](history/06_757923479_Compile_Error.cpp) |
| **07** | `757923503` | ❌ Wrong Answer | 17:30:12 | 遗漏末行：尝试少遍历一行，但遗漏了最后一行字符，仍 WA 于 73/1158 | [07_757923503_Wrong_Answer.cpp](history/07_757923503_Wrong_Answer.cpp) |
| **08** | `757924016` | ❌ Runtime Error | 17:33:50 | 引入 `jiao` 变量：敏锐觉察到“折返拐角”导致自对称重复，尝试检测并 continue，但因调整代码顺序造成数组越界 (Runtime Error) | [08_757924016_Runtime_Error.cpp](history/08_757924016_Runtime_Error.cpp) |
| **09** | `757924323` | ❌ Wrong Answer | 17:35:39 | 数据污染弯路：尝试在拐角检测时利用 `s.pop_back()` 删减字符强制截断，破坏了原始输入数据 WA | [09_757924323_Wrong_Answer.cpp](history/09_757924323_Wrong_Answer.cpp) |
| **10** | `757924461` | ❌ Runtime Error | 17:36:34 | 顺序错位越界：去掉部分条件但保留先更新 `j` 后追加字符的顺序，造成越界访问 (Runtime Error) | [10_757924461_Runtime_Error.cpp](history/10_757924461_Runtime_Error.cpp) |
| **11** | `757924500` | ❌ Wrong Answer | 17:36:45 | 恢复追加顺序：恢复先追加字符再更新 `j`，但保留了未解决的自对称停滞问题 WA | [11_757924500_Wrong_Answer.cpp](history/11_757924500_Wrong_Answer.cpp) |
| **12** | `757924538` | ❌ Wrong Answer | 17:37:06 | 再次尝试截断：再次尝试用 `s.pop_back()` 规避自对称停滞，通过 128/1158 用例，仍因篡改原字符串而 WA | [12_757924538_Wrong_Answer.cpp](history/12_757924538_Wrong_Answer.cpp) |
| **13** | `757925573` | ❌ Compile Error | 17:44:29 | 顿悟折返跨越：领悟在拐角处直接推进对称轴（`times++`）重新计算反射，但缺少闭合大括号 (Compile Error) | [13_757925573_Compile_Error.cpp](history/13_757925573_Compile_Error.cpp) |
| **14** | `757925594` | ✅ **Accepted** | 17:44:38 | 🎉 **最终突破**：补全闭合大括号，**1158 个测试用例全绿 AC，4ms 击败 64.82%！** | [14_757925594_Accepted.cpp](history/14_757925594_Accepted.cpp) |

---

## 3. 错因深层复盘与挫折认知跃迁

### 1. 挫折核心：自对称轴停滞陷阱（反射中心与拐点重合）
- **数学直觉的诞生**：原代码尝试使用轴对称镜像公式来寻找下一个字符下标：
  $$j_{\text{next}} = 2 \times (numRows - 1) \times (times + 1) - j$$
  设单周期跨度为 $T = 2 \times (numRows - 1)$，公式本质上是计算 $j$ 关于对称中心 $T \times (times + 1)$ 的镜像点。
- **陷入僵局的原因**：
  对于第 $0$ 行（$i = 0$），起点 $j = 0$：
  - $times = 0$ 时，镜像点为 $T - 0 = T$；
  - $times$ 递增为 $1$ 时，下一个镜像点为 $2T - T = \mathbf{T}$！
  此时 $j$ **完全没有向前推进，原地停滞在 $T$**！同理对于最后一行 $i = numRows - 1 = T / 2$ 也存在完全一致的自映射问题。

### 2. 挫折衍生：在调试卡壳时的“数据污染”弯路
- 在提交 09 和 12 中，为了打破死循环或跳过重复字符，尝试了 `s.pop_back()`：
  ```cpp
  if (j == 2 * (numRows - 1) * (times + 1) - j) {
      jiao++;
      if (jiao % 2) {
          s.pop_back(); // 致命误区
      }
  }
  ```
- **深度反思**：在只读算法中**绝不可通过修改输入数据来修补控制流**。`s.pop_back()` 不仅销毁了后续行合法的数据，还会导致 `s.size()` 动态缩减，让后续的越界判断与循环彻底失真崩溃。

### 3. 破局顿悟：变量 `jiao`（角）背后的几何真相
- 命名为 `jiao` 极其传神——条件 `next_j == j` 恰恰说明**当前点正好落在了折线的最高拐角（第 0 行）或最低拐角（第 numRows-1 行）**！
- 因为折线的拐角在周期内只有孤立的 **1 个点**，而不是成对对称的 2 个点。一旦命中拐角，镜像就会映照到自身。
- **破局解法极其优雅**：只需判定 `if (next_j == j)`，直接将对称轴往前推进一步 `times++`，再重新算一次镜像，就能干净利落地跨过拐角，奔向下一个真实字符！

---

## 4. 标杆题解与多解法对比

### 解法 A：自研轴对称镜像跨越法（本题 AC 实现）
- **核心代码**（详见 [solution.cpp](solution.cpp)）：
```cpp
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        string result = "";
        for (int i = 0; i < numRows; i++) {
            int j = i;
            int times = 0;
            while (j < s.size()) {
                result += s[j];
                j = 2 * (numRows - 1) * (times + 1) - j;
                if (j == 2 * (numRows - 1) * (times + 1) - j) {
                    times++; // 命中折线拐角，跨越该轴重新计算
                    j = 2 * (numRows - 1) * (times + 1) - j;
                }
                times++;
            }
        }
        return result;
    }
};
```
- **复杂度**：时间复杂度 $O(N)$，空间复杂度严格 $O(1)$（不计返回值）。

### 解法 B：两段步长交替累加法（工程直觉法）
- 每行在前进时交替走两个步长：
  - 下行步长：$step_1 = 2 \times (numRows - 1 - i)$
  - 上行步长：$step_2 = 2 \times i$
- 第一行只走 $step_1$，最后一行只走 $step_2$，中间行二者交替加入。

### 解法 C：状态机上下折返模拟法（面试推荐 0 推导法）
- 利用 `vector<string> rows(numRows)` 模拟小球沿行 $0 \leftrightarrow numRows - 1$ 上下来回弹跳，完全免除下标推导。

---

## 5. 避坑 Checklist
- [ ] $numRows = 1$ 特判：必须优先拦截，否则 $T = 2 \times (numRows - 1) = 0$ 会导致步长为 0 的无限循环！
- [ ] 严禁在只读题中调用 `pop_back()`、`erase()` 等篡改原输入串的方法！
- [ ] 拐点（首行与尾行）单字符特性必须通过跨越轴或单步长特殊处理，不可与中间行的双字符混为一谈。
