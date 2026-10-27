#!/usr/bin/env python3
"""
LeetCode CN (力扣中国) 历史提交记录与错误编码抓取工具
用于提取中途提交过的代码（包括通过与未通过的：Wrong Answer, Compile Error, Runtime Error 等）

注意：
1. 仅当在力扣上点击了【提交】(Submit) 的代码才会被力扣后端持久化存储。如果仅点击【执行代码】(Run Code)，力扣服务器不保留历史。
2. 需要力扣账号的 Cookie（主要是 LEETCODE_SESSION）。

使用方式：
    python3 tools/fetch_submissions.py --slug merge-sorted-array --cookie "你的Cookie"
或者将 Cookie 写入环境变量：
    export LEETCODE_COOKIE="你的Cookie"
    python3 tools/fetch_submissions.py --slug merge-sorted-array
"""

import os
import sys
import json
import argparse
import urllib.request
import urllib.error
from datetime import datetime

LEETCODE_GRAPHQL_URL = "https://leetcode.cn/graphql/"

HEADERS = {
    "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
    "Content-Type": "application/json",
    "Referer": "https://leetcode.cn/",
    "Origin": "https://leetcode.cn",
}

SUBMISSION_LIST_QUERY = """
query mySubmissions($offset: Int!, $limit: Int!, $slug: String) {
  submissionList(offset: $offset, limit: $limit, questionSlug: $slug) {
    lastKey
    hasNext
    submissions {
      id
      statusDisplay
      lang
      runtime
      timestamp
      memory
    }
  }
}
"""

SUBMISSION_DETAIL_QUERY = """
query submissionDetails($submissionId: ID!) {
  submissionDetail(submissionId: $submissionId) {
    id
    code
    timestamp
    statusDisplay
    lang {
      name
      verboseName
    }
    runtimeDisplay
    memoryDisplay
    outputDetail {
      codeOutput
      expectedOutput
      input
      compileError
      runtimeError
      lastTestcase
    }
  }
}
"""


def execute_graphql(query: str, variables: dict, cookie: str):
    headers = dict(HEADERS)
    headers["Cookie"] = cookie

    payload = json.dumps({"query": query, "variables": variables}).encode("utf-8")
    req = urllib.request.Request(LEETCODE_GRAPHQL_URL, data=payload, headers=headers, method="POST")

    try:
        with urllib.request.urlopen(req, timeout=15) as resp:
            data = json.loads(resp.read().decode("utf-8"))
            if "errors" in data:
                print(f"[!] GraphQL 错误: {data['errors']}", file=sys.stderr)
            return data.get("data")
    except urllib.error.HTTPError as e:
        print(f"[!] 网络请求错误 ({e.code}): {e.read().decode('utf-8')}", file=sys.stderr)
        return None
    except Exception as e:
        print(f"[!] 异常: {e}", file=sys.stderr)
        return None


def fetch_submissions_for_slug(slug: str, cookie: str, limit: int = 20):
    print(f"[*] 正在拉取题目 [{slug}] 的最近 {limit} 次提交记录...")
    data = execute_graphql(SUBMISSION_LIST_QUERY, {"offset": 0, "limit": limit, "slug": slug}, cookie)
    if not data or "submissionList" not in data:
        print("[!] 无法获取提交列表，请检查 Cookie 是否有效或是否过期。")
        return []

    submissions = data["submissionList"].get("submissions", [])
    print(f"[+] 找到 {len(submissions)} 次提交记录。")
    return submissions


def fetch_submission_detail(submission_id: str, cookie: str):
    data = execute_graphql(SUBMISSION_DETAIL_QUERY, {"submissionId": str(submission_id)}, cookie)
    if not data or "submissionDetail" not in data:
        return None
    return data["submissionDetail"]


def format_timestamp(ts):
    try:
        return datetime.fromtimestamp(int(ts)).strftime("%Y-%m-%d %H:%M:%S")
    except Exception:
        return str(ts)


def main():
    parser = argparse.ArgumentParser(description="LeetCode CN 历史提交及错误代码提取工具")
    parser.add_argument("--slug", required=True, help="题目英文标识，例如 merge-sorted-array 或 remove-element")
    parser.add_argument("--cookie", default=os.getenv("LEETCODE_COOKIE", ""), help="力扣 Cookie 字符串 (或设置 LEETCODE_COOKIE 环境变量)")
    parser.add_argument("--limit", type=int, default=10, help="最多获取的提交数量 (默认 10)")
    parser.add_argument("--outdir", default="", help="保存代码的目录 (默认在当前终端输出并在控制台展示)")

    args = parser.parse_args()

    cookie = args.cookie.strip()
    if not cookie:
        print("[!] 错误：未提供力扣 Cookie！")
        print("请在浏览器登录 leetcode.cn，按 F12 打开开发者工具，在网络 (Network) 请求头中复制 Cookie，")
        print("并通过 --cookie 参数或 LEETCODE_COOKIE 环境变量传入。")
        sys.exit(1)

    submissions = fetch_submissions_for_slug(args.slug, cookie, args.limit)
    if not submissions:
        print("[-] 未找到相关提交。")
        return

    print("=" * 70)
    for idx, sub in enumerate(submissions):
        sub_id = sub["id"]
        status = sub.get("statusDisplay")
        lang = sub.get("lang")
        time_str = format_timestamp(sub.get("timestamp"))

        status_emoji = "✅" if status == "Accepted" else "❌"
        print(f"[{idx + 1}] ID: {sub_id} | 状态: {status_emoji} {status} | 语言: {lang} | 时间: {time_str}")

        # 拉取详细代码
        detail = fetch_submission_detail(sub_id, cookie)
        if detail:
            code = detail.get("code", "")
            output_detail = detail.get("outputDetail") or {}
            
            print("-" * 50)
            if status != "Accepted":
                print(f"[!] 报错状态详情: {status}")
                if output_detail.get("compileError"):
                    print(f"编译报错:\n{output_detail['compileError']}")
                if output_detail.get("runtimeError"):
                    print(f"运行报错:\n{output_detail['runtimeError']}")
                if output_detail.get("lastTestcase"):
                    print(f"未通过测试用例: {output_detail['lastTestcase']}")
                if output_detail.get("codeOutput"):
                    print(f"实际输出: {output_detail['codeOutput']}")
                if output_detail.get("expectedOutput"):
                    print(f"期望输出: {output_detail['expectedOutput']}")

            if args.outdir:
                os.makedirs(args.outdir, exist_ok=True)
                ext = ".cpp" if "cpp" in lang.lower() else ".txt"
                filename = f"submission_{sub_id}_{status.replace(' ', '_')}{ext}"
                filepath = os.path.join(args.outdir, filename)
                with open(filepath, "w", encoding="utf-8") as f:
                    f.write(f"// 提交时间: {time_str}\n")
                    f.write(f"// 状态: {status}\n\n")
                    f.write(code)
                print(f"[+] 已将代码写入: {filepath}")
            else:
                print("提交代码预览 (前 8 行):")
                lines = code.splitlines()
                for line in lines[:8]:
                    print(f"    {line}")
                if len(lines) > 8:
                    print(f"    ... (共 {len(lines)} 行)")
            print("-" * 50)


if __name__ == "__main__":
    main()
