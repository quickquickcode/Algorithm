# 🧠 Algorithm Mastery: LeetCode 面试经典 150 题复盘与成长随笔库

> **“记录失败，比记录成功更有价值。”**  
> 本仓库不仅记录最终通过的代码，更专注于捕获刷题过程中的**思维卡点**、**错误尝试**、**语法纠偏**与**认知跃迁（Aha Moment）**。通过建立结构化的错题复盘档案，帮助分析底层思维漏洞，为中后期高效复习提供第一手真实复盘资料。

---

## 🎯 仓库核心机制与设计哲学

```
   [初见直觉] ──────> [踩坑博物馆] ──────> [认知跃迁] ──────> [标杆模式] ──────> [定期复盘]
  直觉如何产生?       中途写错的代码        哪一步想通了?       标准C++解法        艾宾浩斯复习
  为什么会卡住?       (CE / WA / RE)       从混沌到清晰        时空复杂度         错因打卡跟踪
```

1. **真实记录挣扎过程**：每一题不仅有最终的 `solution.cpp`，还保留 `solution_v1_wrong.cpp`、`solution_v2_wrong.cpp` 等中途错误版本，并逐一分析致命缺陷。
2. **沉淀通用认知模型**：提炼 STL 底层机制（如 `vector` 内存模型与下溢陷阱）与算法核心思维（如双指针不变量）。
3. **闭环复习看板**：采用三色掌握度标记（🔴 严重卡壳 / 🟡 踩坑修正 / 🟢 一次通过），结合艾宾浩斯间隔复习。

---

## 📂 仓库目录导航

```
Algorithm/
├── README.md                      # 全局看板、150 题追踪图谱与方法论
├── docs/                          # 基础理论与核心专题总结
│   ├── cpp-stl-notes.md           # C++ STL 核心避坑手册（vector、引用、迭代器、下溢漏洞）
│   └── two-pointers-patterns.md   # 双指针体系模型（逆向、快慢、对撞覆盖法）
├── templates/                     # 随笔与题解模板
│   └── problem_template.md        # 新题复盘随笔模板（直接复制使用）
├── tools/                         # 自动化工具箱
│   ├── fetch_submissions.py       # 力扣 GraphQL 提交记录与错误代码抓取 CLI
│   └── README.md                  # 力扣提交流程与 CLI / VS Code 插件使用指南
└── problems/                      # 题目归档（按 Top Interview 150 专题分类）
    └── 01_Array_String/           # 专题 1：数组 / 字符串
        ├── 0088_merge-sorted-array/
        └── 0027_remove-element/
```

---

## 📊 「面试经典 150 题」总览与当前进度看板

- **总进度**：`3 / 150` 完成
- **状态统计**：🟢 一次通过: 2 | 🟡 踩坑修正: 1 | 🔴 待重做: 0

### 1. 数组 / 字符串 (Array / String)
| 题号 | 题目名称 | 难度 | 掌握状态 | 核心考点 / 突破口 | 随笔链接 |
| :---: | :--- | :---: | :---: | :--- | :---: |
| 88 | [合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/) | 🟢 简单 | 🟡 踩坑修正 | 逆向双指针；后置空位利用；避免循环内 insert | [详尽复盘笔记](problems/01_Array_String/0088_merge-sorted-array/README.md) |
| 27 | [移除元素](https://leetcode.cn/problems/remove-element/) | 🟢 简单 | 🟢 一次通过 | 快慢双指针覆盖；内层 while 边界防越界；覆盖取代交换 | [详尽复盘笔记](problems/01_Array_String/0027_remove-element/README.md) |
| 26 | [删除有序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/) | 🟢 简单 | 🟢 一次通过 | 快慢指针有序去重；值与下标区分；`slow+1` 长度偏移 | [详尽复盘笔记](problems/01_Array_String/0026_remove-duplicates/README.md) |
| 80 | [删除有序数组中的重复项 II](https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/) | 🟡 中等 | ⚪ 未开始 | 快慢指针保留 k 个 | 待添加 |
| 169 | [多数元素](https://leetcode.cn/problems/majority-element/) | 🟢 简单 | ⚪ 未开始 | Boyer-Moore 投票算法 | 待添加 |
| 189 | [轮转数组](https://leetcode.cn/problems/rotate-array/) | 🟡 中等 | ⚪ 未开始 | 三次翻转法 | 待添加 |
| 121 | [买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/) | 🟢 简单 | ⚪ 未开始 | 前缀最小值维护 | 待添加 |
| 122 | [买卖股票的最佳时机 II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/) | 🟡 中等 | ⚪ 未开始 | 贪心收集正收益 | 待添加 |
| 55 | [跳跃游戏](https://leetcode.cn/problems/jump-game/) | 🟡 中等 | ⚪ 未开始 | 贪心维护最远边界 | 待添加 |
| 45 | [跳跃游戏 II](https://leetcode.cn/problems/jump-game-ii/) | 🟡 中等 | ⚪ 未开始 | 贪心边界跳跃 | 待添加 |
| ... | *(后续 140 题已按专题预备好目录架构)* | | | | |

---

## 💡 前两题深层次踩坑归纳与思维升级

在刷完前两题（88 题和 27 题）后，梳理出以下具有**普适指导意义**的思维进化：

### 1. 从“直觉前向操作”跃迁到“空间逆向利用”
- **初见痛点**：直觉习惯从头开始操作（从下标 0 往后），但在有序合并（88题）中，正向插入会直接覆盖或推挤未处理的数据，导致算法不得不陷入 $O(N^2)$ 的 `insert`。
- **思维升级**：**观察空闲空间在哪里**。`nums1` 后面空着 $n$ 个空位，从后往前填，大数先入库，不仅不会覆盖有效元素，而且连临时数组都省了。

### 2. 从“繁琐交换思维”跃迁到“纯粹覆盖思维”
- **初见痛点**：在移除元素（27题）中，第一反应是像快速排序那样“找到目标就交换到末尾”，甚至试图用 `resize()` 去强行截断数组。这引入了内层循环无界、指针原地打转、无意义计数等一系列严重 bug。
- **思维升级**：力扣评测只在乎前 $k$ 个有效数据是谁，后面的垃圾数据根本不需要费心“交换”。直接用**快慢指针（探路者 + 守门员）**一路覆盖过来，代码极简且零越界风险。

### 3. C++ 刷题的“血泪边界法则”
- **下标与迭代器绝不混淆**：`nums[i]` 必须是整型下标，`nums.begin() + i` 才是迭代器。
- **任何内层 `while` 自增自减必须带界**：`while (idx < n && nums[idx] != val)`，严禁裸跑无界 `while`。
- **慎用 `size() - 1`**：无符号 `size_t` 在 0 减 1 时会变成超级大数，引发段错误。

---

## 🛠️ 力扣提交抓取工具与工作流

想把中途在力扣网页上写的报错代码同步下来？
```bash
# 获取某题的所有历史提交（包括 WA, CE, RE 代码和未通过用例）
python3 tools/fetch_submissions.py --slug merge-sorted-array --cookie "你的LEETCODE_COOKIE"
```
具体教程参见 [tools/README.md](tools/README.md)。

---

## 📝 新题记录工作流（如何使用本仓库）

1. **开题**：从 `templates/problem_template.md` 复制一份到对应的题目子目录（如 `problems/01_Array_String/0026_remove-duplicates/README.md`）。
2. **写下第一直觉**：做题前花 2 分钟记录最初的思路和困惑点。
3. **记录中途报错**：如果提交失败了，**不要直接删掉代码**！把它另存为 `solution_v1_wrong.cpp`，写下当时为什么报错。
4. **顿悟与正解**：通过后，把标准解法存入 `solution.cpp`，并在 `README.md` 提炼出属于自己的“认知跃迁（Aha Moment）”。
5. **定期复习**：每周看一眼标记为 🟡 或 🔴 的题目，只看当时的错因和 Checklist，闭卷重写一次。
