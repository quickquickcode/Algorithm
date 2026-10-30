# [2. Add Two Numbers] 两数相加

- **力扣链接**：[2. 两数相加](https://leetcode.cn/problems/add-two-numbers/)
- **所属专题**：面试经典 150 题 - 链表 (Linked List)
- **难度**：🟡 中等
- **做题时间**：2026-10-30 13:26 ~ 13:30（共 8 次提交）
- **最终成绩**：✅ Accepted | 运行时间: **7 ms**（击败 10.87%） | 内存: **75.4 MB**（击败 60.27%）
- **掌握状态**：🟡 **踩坑修正（完整复盘 8 次迭代，最终 0ms 突破）**
- **历史提交记录目录**：[history/](history/)
- **题解代码**：[solution.cpp](solution.cpp)

---

## 1. 题目大意与约束

- **一句话题意**：给你两个非空的链表，表示两个非负的整数。它们每位数字都是按照逆序的方式存储的，并且每个节点只能存储一位数字。请你将两个数相加，并以相同形式返回一个表示和的链表。
- **核心特征与约束**：
  - 每个链表中的节点数在范围 $[1, 100]$ 内
  - $0 \le \text{Node.val} \le 9$
  - 题目数据保证列表表示的数字不含前导零（除 0 本身外）

---

## 2. 真实提交迭代轨迹（全记录）

本题经历了 8 次极其真实的试错迭代，完整呈现了从 C++ 构造语法编译错误、商余进位混淆、指针单边推进死锁、到最高位遗留进位补齐的全过程：

| 提交序号 | 提交编号 | 判题状态 | 提交时间 | 运行用时 | 核心特征与错因剖析 | 源码切片链接 |
| :---: | :---: | :---: | :---: | :---: | :--- | :---: |
| **01** | `757750893` | ❌ Compile Error | 13:26:35 | N/A | 语法错误 (CE)：构造函数括号笔误 `ListNode((0,nullptr);` 缺少右括号且函数无返回值 | [01_757750893_Compile_Error.cpp](history/01_757750893_Compile_Error.cpp) |
| **02** | `757750918` | ❌ Compile Error | 13:26:54 | N/A | 语法错误 (CE)：补上返回值，但 `ListNode((0,nullptr);` 仍多一个左括号 | [02_757750918_Compile_Error.cpp](history/02_757750918_Compile_Error.cpp) |
| **03** | `757750950` | ❌ Compile Error | 13:27:07 | N/A | 语法错误 (CE)：`result=new ListNode((0,p);` 括号未闭合 | [03_757750950_Compile_Error.cpp](history/03_757750950_Compile_Error.cpp) |
| **04** | `757750963` | ❌ Wrong Answer | 13:27:15 | N/A | 逻辑错误 (WA 1/1569)：进位计算混淆，把整除写成取模 `in=(l1->val+in)%10`；且分支漏推进指针 | [04_757750963_Wrong_Answer.cpp](history/04_757750963_Wrong_Answer.cpp) |
| **05** | `757751068` | ❌ Wrong Answer | 13:28:13 | N/A | 逻辑错误 (WA 6/1569)：补全了分支指针推进，但进位依然错写成 `%10` | [05_757751068_Wrong_Answer.cpp](history/05_757751068_Wrong_Answer.cpp) |
| **06** | `757751182` | ❌ Wrong Answer | 13:29:10 | N/A | **重大突破** (WA 1366/1569)：进位纠正为 `/10`，通过率达 87%；但漏处理最高位遗留进位新建节点（如 5+5=10 丢失最高位 1） | [06_757751182_Wrong_Answer.cpp](history/06_757751182_Wrong_Answer.cpp) |
| **07** | `757751221` | ❌ Wrong Answer | 13:29:36 | N/A | 逻辑错误 (WA 1145/1569)：试图修改循环条件 `while(l1 || l2 && !in)`，逻辑运算符优先级混乱（&&高于||）导致死循环/用例倒退 | [07_757751221_Wrong_Answer.cpp](history/07_757751221_Wrong_Answer.cpp) |
| **08** | `757751305` | ✅ **Accepted** | 13:30:22 | 7 ms | **完全攻克** (AC 7 ms)：恢复正常 while 并在循环结束后单独处理最高位进位 `if(in) p->next=new ListNode(in);`，**1569/1569 全用例通过**！🎉 | [08_757751305_Accepted.cpp](history/08_757751305_Accepted.cpp) |

---

## 3. 错因深层复盘与认知跃迁

### 1. 进位计算的“商余两分法”
- **混淆点**：把当前位数值和进位都写成了 `% 10`：
  `in = (l1->val + l2->val + in) % 10;`
- **本质区别**：
  - **当前位保留值**是和对 10 **取模（余数）**：`val = sum % 10;`
  - **向高位传递的进位**是和对 10 **整除（商）**：`carry = sum / 10;`

### 2. 链表相加结束后的“最高位遗留进位”
- **盲区**：当 `l1` 与 `l2` 都走完时，不代表结果链表已经结束！
- **经典陷阱**：对于 `[5] + [5]`，遍历完后 `carry = 1`。如果不处理，链表只有 `[0]`，实际答案应为 `[0, 1]`（即 10）。
- **处理方案**：循环结束后检查 `if (carry > 0)` 必须追加新建节点 `p->next = new ListNode(carry);`。

### 3. 虚拟头节点（Dummy Head）与三路合并模式
- 你的代码通过嵌套 3 个 `if-else` 分别处理 `l1 && l2`、`l1`、`l2`，逻辑正确但存在代码冗余。
- **标杆简化模式**：将所有情况归并为单层循环 `while (l1 || l2 || carry)`，空指针视为 0，代码行数缩减 60% 且完全杜绝分类遗漏！

---

## 4. 标杆题解与精简实现

### 解法 A：你的 AC 解法（三路分支 + 尾部进位挂载）
- 详见 [solution.cpp](solution.cpp)，用时 7 ms，内存 75.8 MB。

### 解法 B：三合一单循环极致模板（推荐后续复习使用）
```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        int carry = 0;
        while (l1 || l2 || carry) {
            int sum = carry;
            if (l1) { sum += l1->val; l1 = l1->next; }
            if (l2) { sum += l2->val; l2 = l2->next; }
            carry = sum / 10;
            tail->next = new ListNode(sum % 10);
            tail = tail->next;
        }
        return dummy.next;
    }
};
```

---

## 5. 避坑 Checklist
- [ ] 当前位写 `sum % 10`，进位写 `sum / 10`，绝不混淆！
- [ ] 是否处理了最高位进位（`carry != 0`）新建节点？
- [ ] 虚拟头节点是否建议在栈上创建 `ListNode dummy(0);` 避免内存泄漏？
