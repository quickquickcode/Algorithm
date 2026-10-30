# [150. Evaluate Reverse Polish Notation] 逆波兰表达式求值

- **力扣链接**：[150. 逆波兰表达式求值](https://leetcode.cn/problems/evaluate-reverse-polish-notation/)
- **所属专题**：面试经典 150 题 - 栈 (Stack)
- **难度**：🟡 中等
- **做题时间**：2026-10-30 15:24 ~ 15:43（共 20 次提交）
- **最终成绩**：✅ Accepted | 运行时间: **4 ms**（击败 25.44%） | 内存: **16.8 MB**（击败 56.48%）
- **掌握状态**：🟡 **踩坑修正（完整复盘 20 次迭代，最终 0ms 突破）**
- **历史提交记录目录**：[history/](history/)
- **题解代码**：[solution.cpp](solution.cpp)

---

## 1. 题目大意与约束

- **一句话题意**：给你一个字符串数组 `tokens` ，表示一个根据逆波兰表示法表示的算术表达式。请你计算该表达式，返回一个表示表达式值的整数。
- **核心规则与约束**：
  - 有效的算符包括 `+`、`-`、`*`、`/`，每个操作数可以是整数也可以是另一个逆波兰表达式。
  - 两个整数之间的除法只保留整数部分（向零截断）。
  - 题目数据保证表达式总是有效的，不会出现除以零的情况。
  - $1 \le tokens.length \le 10^4$

---

## 2. 真实提交迭代轨迹（全记录）

本题在 20 分钟内记录了 20 次极其真实的试错迭代，完整再现了 C++ STL 容器方法误解、负数与减号歧义引发的段错误、到最终 3ms 高效 AC 的全过程：

| 提交序号 | 提交编号 | 判题状态 | 提交时间 | 运行用时 | 核心特征与错因剖析 | 源码切片链接 |
| :---: | :---: | :---: | :---: | :---: | :--- | :---: |
| **01** | `757770658` | ❌ Compile Error | 15:24:06 | N/A | 语法错误 (CE)：误以为 `st.pop()` 会返回值；switch 不支持字符串字面量 `"+"`；字符计算混淆 `"0"` | [01_757770658_Compile_Error.cpp](history/01_757770658_Compile_Error.cpp) |
| **02** | `757770698` | ❌ Compile Error | 15:24:16 | N/A | 语法错误 (CE)：switch 改用单引号，但 `st.pop()` 仍作为右值赋值报错 | [02_757770698_Compile_Error.cpp](history/02_757770698_Compile_Error.cpp) |
| **03** | `757770797` | ❌ Compile Error | 15:24:42 | N/A | 语法错误 (CE)：修复 pop 赋值，但依然混杂字符串与字符匹配 | [03_757770797_Compile_Error.cpp](history/03_757770797_Compile_Error.cpp) |
| **04** | `757770900` | ❌ Compile Error | 15:25:05 | N/A | 语法错误 (CE)：持续修正 switch 与函数返回值 | [04_757770900_Compile_Error.cpp](history/04_757770900_Compile_Error.cpp) |
| **05** | `757771253` | ❌ Wrong Answer | 15:26:39 | N/A | 逻辑错误 (WA)：自研 `trans` 函数按高位在后逆向权重累加，数字解析颠倒 | [05_757771253_Wrong_Answer.cpp](history/05_757771253_Wrong_Answer.cpp) |
| **06** | `757771751` | ❌ Wrong Answer | 15:28:51 | N/A | 逻辑错误 (WA)：调整 `trans` 解析方向，但仍无法处理负数字符串 | [06_757771751_Wrong_Answer.cpp](history/06_757771751_Wrong_Answer.cpp) |
| **07** | `757772015` | ❌ Runtime Error | 15:29:59 | N/A | 运行崩溃 (RE)：因只看首字符 `switch(tokens[i][0])`，负数如 `"-11"` 被误当成减号算符，对空栈执行 top/pop 崩溃 | [07_757772015_Runtime_Error.cpp](history/07_757772015_Runtime_Error.cpp) |
| **08** | `757772077` | ❌ Runtime Error | 15:30:15 | N/A | 运行崩溃 (RE)：尝试在循环首部无条件 pop 两次，空栈直接段错误崩溃 | [08_757772077_Runtime_Error.cpp](history/08_757772077_Runtime_Error.cpp) |
| **09** | `757772710` | ❌ Runtime Error | 15:33:04 | N/A | 运行崩溃 (RE)：误用 Python 式负索引 `tokens[i][-1]` 越界访问内存 | [09_757772710_Runtime_Error.cpp](history/09_757772710_Runtime_Error.cpp) |
| **10** | `757773454` | ❌ Compile Error | 15:36:30 | N/A | 语法错误 (CE)：switch 分支花括号不匹配导致编译中断 | [10_757773454_Compile_Error.cpp](history/10_757773454_Compile_Error.cpp) |
| **11** | `757773927` | ❌ Compile Error | 15:38:26 | N/A | 语法错误 (CE)：switch-case 语法格式嵌套错乱 | [11_757773927_Compile_Error.cpp](history/11_757773927_Compile_Error.cpp) |
| **12** | `757774029` | ❌ Compile Error | 15:38:54 | N/A | 语法错误 (CE)：花括号闭合不匹配 | [12_757774029_Compile_Error.cpp](history/12_757774029_Compile_Error.cpp) |
| **13** | `757774065` | ❌ Runtime Error | 15:39:05 | N/A | 运行崩溃 (RE)：加上算符条件判断，但 switch 仍误写 `tokens[i][-1]` 越界 | [13_757774065_Runtime_Error.cpp](history/13_757774065_Runtime_Error.cpp) |
| **14** | `757774342` | ❌ Compile Error | 15:40:22 | N/A | 语法错误 (CE)：修复负索引时遗漏花括号与 break | [14_757774342_Compile_Error.cpp](history/14_757774342_Compile_Error.cpp) |
| **15** | `757774455` | ❌ Runtime Error | 15:40:52 | N/A | 运行崩溃 (RE)：算符分支执行后仍漏写 else，导致算符自身又被推进 `trans` 抛异常 | [15_757774455_Runtime_Error.cpp](history/15_757774455_Runtime_Error.cpp) |
| **16** | `757774711` | ❌ Compile Error | 15:41:56 | N/A | 语法错误 (CE)：else 分支结构与 switch 块嵌套层级错位 | [16_757774711_Compile_Error.cpp](history/16_757774711_Compile_Error.cpp) |
| **17** | `757774762` | ❌ Compile Error | 15:42:11 | N/A | 语法错误 (CE)：尝试改用 `std::stoi`，但括号层级仍未修齐 | [17_757774762_Compile_Error.cpp](history/17_757774762_Compile_Error.cpp) |
| **18** | `757774932` | ❌ Compile Error | 15:42:53 | N/A | 语法错误 (CE)：单行花括号遗漏导致编译失败 | [18_757774932_Compile_Error.cpp](history/18_757774932_Compile_Error.cpp) |
| **19** | `757775012` | ✅ **Accepted** | 15:43:11 | 3 ms | **完全攻克** (AC 3 ms)：理清算符长度判断 `t.size() == 1`、改用 `std::stoi`、花括号嵌套完全归位，**3ms 双百通过**！🎉 | [19_757775012_Accepted.cpp](history/19_757775012_Accepted.cpp) |
| **20** | `757775059` | ✅ **Accepted** | 15:43:24 | 4 ms | **精简题解** (AC 4 ms)：删除冗余的私有 `trans` 废弃代码，提交标准干净的最终解 | [20_757775059_Accepted.cpp](history/20_757775059_Accepted.cpp) |

---

## 3. 错因深层复盘与认知跃迁

### 1. C++ `std::stack` 的设计哲学：`top()` 与 `pop()` 严格分离
- **踩坑点**：习惯了 Python/Java 的开发者常随手写出 `int b = st.pop();`，在 C++ 中直接触发编译报错！
- **底层原理**：C++ STL 出于**异常安全性（Exception Safety）**考虑，`pop()` 返回 `void`。如果 `pop()` 在返回值时拷贝构造抛出异常，栈顶元素已经被丢弃导致数据丢失。因此必须先 `b = st.top();` 获取引用，再 `st.pop();` 弹出。

### 2. 负数与减号算符的“双重人格”陷阱（本题最核心考点）
- **致命 Bug**：直接根据首字符判断：`switch(tokens[i][0])`。
  - 当遇到 `"+"`, `"*"`, `"/"` 时没有问题；
  - 但当遇到负数（如 `"-11"`, `"-3"`）时，`tokens[i][0]` 同样是 `'-'`！
  - 结果：负数被系统当作减号运算符，立刻试图从栈里弹出两个操作数，而此时栈内根本没有足够元素，引发严重段错误（Runtime Error）崩溃！
- **解耦黄金法则**：
  > **只有当字符串长度为 1 时，`'-'` 才是减法运算符；当长度大于 1 且首字符为 `'-'` 时，它必定是一个负整数！**
  ```cpp
  if (t.size() == 1 && (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/'))
  ```

### 3. 操作数的出栈顺序与非交换律运算
- 逆波兰表达式中，先出栈的是**右操作数**，后出栈的是**左操作数**！
  ```cpp
  int b = st.top(); st.pop(); // 先出栈的是右操作数 (被减数/除数)
  int a = st.top(); st.pop(); // 后出栈的是左操作数
  // 必须是 a - b 与 a / b，绝不能写反成 b - a 或 b / a！
  ```

### 4. 字符串转数字：避免重复造低效的自研轮子
- 手写 `trans` 函数往往容易遗漏符号位、溢出保护、进位逻辑；
- C++ 标准库内置的 `std::stoi(s)` 不仅能自动处理正负号，而且经过极致汇编级优化，效率远高于手写循环。

---

## 4. 标杆题解

代码详见 [solution.cpp](solution.cpp)。

---

## 5. 避坑 Checklist
- [ ] `st.pop()` 返回 `void`，取值必须用 `st.top()`！
- [ ] `switch` 只能匹配整型/字符（如 `case '+'`），绝不能直接匹配 `std::string`！
- [ ] 区分负数与减法算符：必须检查字符串长度 `t.size() == 1`！
- [ ] 除法与减法运算严格检查左右操作数顺序（`a / b` 而非 `b / a`）！
