# 力扣 (LeetCode) 历史提交与错误代码提取指南

本目录提供了用于获取你在力扣中途写过的历史代码（特别是**未通过的错误编码**、**编译报错**、**未通过用例**）的工具与方法说明。

---

## 核心机制：力扣如何保存你的代码？

在力扣网页端或插件端刷题时，有两种执行模式：

| 模式 | 按钮 | 服务器行为 | 是否可事后找回 |
| :--- | :--- | :--- | :--- |
| **执行代码** | Run Code | 仅在后台临时沙箱运行单组测试用例 | ❌ **不保存**。网页关闭或刷新后丢失 |
| **提交代码** | Submit | 提交到主评测机，生成全局唯一的 `submission_id` | ✅ **永久保存**。包含完整代码、报错信息、未通过测试用例 |

> **建议刷题好习惯**：
> 每当你写完一个阶段性思路，**即使自知可能还有边界没处理好，也可以大胆点击【提交】**！
> 这样力扣服务器就会永久为你留下一条提交记录，方便后续复盘你的“中途挣扎状态”。

---

## 方案一：仓库内置的专属提取脚本 (`fetch_submissions.py`)

本仓库已为你内置好 Python 脚本，基于力扣中国官方 GraphQL 接口编写，支持自动拉取某题的所有提交历史（包含通过的、解答错误的、编译报错的代码和报错详情），并可直接导出为 `.cpp` 源码文件。

### 1. 获取你的力扣 Cookie
1. 打开浏览器登录 [leetcode.cn](https://leetcode.cn/)。
2. 按 `F12` 打开“开发者工具”（Developer Tools），切换到 **网络（Network）** 选项卡。
3. 刷新一下页面或点击任意请求，在请求头（Request Headers）中找到 `Cookie`。
4. 复制其中的整段 Cookie（关键字段是 `LEETCODE_SESSION`）。

### 2. 使用方法

#### 查看某题最近提交历史与报错详情：
```bash
python3 tools/fetch_submissions.py --slug merge-sorted-array --cookie "你的Cookie内容"
```

#### 将所有历史提交（含错误代码）直接导出到目录：
```bash
python3 tools/fetch_submissions.py --slug merge-sorted-array --cookie "你的Cookie内容" --outdir problems/01_Array_String/0088_merge-sorted-array/history/
```

#### 或将 Cookie 设置为环境变量（推荐）：
```bash
export LEETCODE_COOKIE="你的Cookie内容"
python3 tools/fetch_submissions.py --slug remove-element
```

---

## 方案二：VS Code 官方 / 社区插件（可视化推荐）

如果你使用 VS Code 进行本地刷题，最便捷的工具是安装扩展：
- **插件名称**：`LeetCode`（推荐由 ShengChen 维护的力扣插件，支持 LeetCode CN 切换）
- **功能特性**：
  1. 在左侧力扣题库树状图中找到做过的题。
  2. 点击题目后，可以在子菜单中看到 **`Submissions`**（提交历史）。
  3. 点击任意一条历史（哪怕是 `Wrong Answer` 或 `Runtime Error`），VS Code 都会直接开一个只读窗口，展示当时提交的具体代码以及失败的测试用例。

---

## 方案三：命令行 CLI 工具 (`leetcode-cli`)

如果你喜欢纯命令行终端操作：
- **项目**：[skygragon/leetcode-cli](https://github.com/skygragon/leetcode-cli) 或 [leetcode-tools/leetcode-cli](https://github.com/leetcode-tools/leetcode-cli)
- **安装**：
  ```bash
  npm install -g leetcode-cli
  ```
- **配置力扣中国**：
  ```bash
  leetcode config -t leetcode.cn
  leetcode user -l
  ```
- **查看提交历史**：
  ```bash
  leetcode submission <submission_id>
  ```
- **缺陷说明**：由于力扣国内站防爬和登录机制频繁更新，第三方 node CLI 经常遇到登录鉴权失效问题。相比之下，方案一的 GraphQL 脚本和方案二的 VS Code 插件更加稳定可靠。
