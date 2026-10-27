#!/usr/bin/env python3
"""
LeetCode CN (力扣中国) 历史提交记录与代码提取工具
使用力扣官方 REST / GraphQL 接口，提取做题过程中所有的提交记录（包括 Accepted, Wrong Answer, Compile Error 等）

使用方式：
    python3 tools/fetch_submissions.py --slug remove-element --cookie "你的Cookie"
或：
    export LEETCODE_COOKIE="你的Cookie"
    python3 tools/fetch_submissions.py --slug remove-element --outdir problems/01_Array_String/0027_remove-element/history/
"""

import os
import sys
import json
import argparse
import subprocess
from datetime import datetime

USER_AGENT = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"


def parse_csrf(cookie_str: str) -> str:
    for item in cookie_str.split(";"):
        item = item.strip()
        if item.startswith("csrftoken="):
            return item.split("=", 1)[1]
    return ""


def solve_waf_challenge(html: str) -> str:
    """通过 Node.js 沙箱解算阿里 WAF 挑战，生成 alicfw 相关 Cookie"""
    import re
    m0 = re.search(r'name="parm_0"\s+value=\s*(-?\d+)', html)
    m1 = re.search(r'name="parm_1"\s+value=\s*(-?\d+)', html)
    script_m = re.search(r'<script type="text/javascript">([\s\S]*?)</script>', html)
    if not (m0 and m1 and script_m):
        return ""
    p0, p1, script = m0.group(1), m1.group(1), script_m.group(1)
    runner = """
    const fs = require('fs');
    const vm = require('vm');
    const input = JSON.parse(fs.readFileSync(0, 'utf-8'));
    let cookies = [];
    const document = {
      getElementById: (id) => ({ value: id === "parm_0" ? input.p0 : input.p1 }),
      documentElement: { clientWidth: 1920, clientHeight: 1080 },
      location: { protocol: "https:", host: "leetcode.cn" },
      set cookie(val) { cookies.push(val.split(";")[0]); },
      get cookie() { return cookies.join("; "); }
    };
    const window = { location: { protocol: "https:", host: "leetcode.cn", reload: () => {} } };
    const context = { document, window, console: { log: () => {} }, parseInt, escape, Date };
    vm.createContext(context);
    vm.runInContext(input.script + "\\ncheck();", context);
    process.stdout.write(cookies.join("; "));
    """
    proc = subprocess.run(
        ["node", "-e", runner],
        input=json.dumps({"p0": p0, "p1": p1, "script": script}),
        capture_output=True,
        text=True
    )
    return proc.stdout.strip()


def ensure_waf_cookies(cookie_str: str) -> str:
    """若缺少有效 alicfw 防火墙 Cookie，则通过 Node.js 快速解算挑战"""
    cmd = [
        "curl", "-s", "https://leetcode.cn/api/submissions/merge-sorted-array/",
        "-H", f"Cookie: {cookie_str}",
        "-H", f"User-Agent: {USER_AGENT}"
    ]
    res = subprocess.run(cmd, capture_output=True, text=True, timeout=10)
    if "onload=\"check()\"" in res.stdout:
        calc_cookies = solve_waf_challenge(res.stdout)
        if calc_cookies:
            cookie_str += "; " + calc_cookies
    return cookie_str


def get_submissions_list(slug: str, cookie: str):
    csrf = parse_csrf(cookie)
    cmd = [
        "curl", "-s", f"https://leetcode.cn/api/submissions/{slug}/",
        "-H", f"Cookie: {cookie}",
        "-H", f"User-Agent: {USER_AGENT}",
        "-H", f"Referer: https://leetcode.cn/problems/{slug}/submissions/",
        "-H", f"x-csrftoken: {csrf}"
    ]
    res = subprocess.run(cmd, capture_output=True, text=True)
    try:
        data = json.loads(res.stdout)
        return data.get("submissions_dump", [])
    except Exception as e:
        print(f"[!] 解析提交列表失败: {e}", file=sys.stderr)
        return []


def get_submission_detail(sub_id: str, cookie: str):
    csrf = parse_csrf(cookie)
    query = """
    query submissionDetails($submissionId: ID!) {
      submissionDetail(submissionId: $submissionId) {
        id
        code
        timestamp
        statusDisplay
        lang
        runtimeDisplay: runtime
        memoryDisplay: memory
        runtimePercentile
        memoryPercentile
        passedTestCaseCnt
        totalTestCaseCnt
      }
    }
    """
    req_body = json.dumps({"operationName": "submissionDetails", "query": query, "variables": {"submissionId": str(sub_id)}})
    cmd = [
        "curl", "-s", "https://leetcode.cn/graphql/",
        "-H", f"Cookie: {cookie}",
        "-H", f"User-Agent: {USER_AGENT}",
        "-H", f"Referer: https://leetcode.cn/submissions/detail/{sub_id}/",
        "-H", "Content-Type: application/json",
        "-H", f"x-csrftoken: {csrf}",
        "--data", req_body
    ]
    res = subprocess.run(cmd, capture_output=True, text=True)
    try:
        return json.loads(res.stdout).get("data", {}).get("submissionDetail")
    except Exception as e:
        return None


def get_runtime_distribution(sub_id: str, cookie: str):
    """获取执行用时分布直方图数据"""
    cmd = [
        "curl", "-s", f"https://leetcode.cn/submissions/api/runtime_distribution/{sub_id}/",
        "-H", f"Cookie: {cookie}",
        "-H", f"User-Agent: {USER_AGENT}",
        "-H", f"Referer: https://leetcode.cn/submissions/detail/{sub_id}/"
    ]
    res = subprocess.run(cmd, capture_output=True, text=True)
    try:
        data = json.loads(res.stdout)
        formatted = json.loads(data.get("runtime_distribution_formatted", "{}"))
        return formatted.get("distribution", [])
    except Exception:
        return []


def main():
    parser = argparse.ArgumentParser(description="LeetCode CN 历史提交及代码/用时击败率提取工具")
    parser.add_argument("--slug", required=True, help="题目英文标识，例如 merge-sorted-array 或 remove-element")
    parser.add_argument("--cookie", default=os.getenv("LEETCODE_COOKIE", ""), help="力扣 Cookie 字符串 (或设置 LEETCODE_COOKIE 环境变量)")
    parser.add_argument("--limit", type=int, default=20, help="最多获取的提交数量")
    parser.add_argument("--outdir", default="", help="保存代码的目录 (默认在终端展示)")

    args = parser.parse_args()
    cookie = args.cookie.strip()
    if not cookie:
        # 自动尝试从本地 cookie.txt 文件读取
        candidates = [
            "cookie.txt",
            os.path.join(os.path.dirname(__file__), "..", "cookie.txt"),
            os.path.expanduser("~/.leetcode_cookie")
        ]
        for cpath in candidates:
            if os.path.exists(cpath):
                try:
                    with open(cpath, "r", encoding="utf-8") as f:
                        cookie = f.read().strip()
                    if cookie:
                        break
                except Exception:
                    pass

    if not cookie:
        print("[!] 错误：未提供力扣 Cookie！请通过 --cookie、LEETCODE_COOKIE 环境变量或 cookie.txt 提供。")
        sys.exit(1)

    cookie = ensure_waf_cookies(cookie)
    submissions = get_submissions_list(args.slug, cookie)
    if not submissions:
        print(f"[-] 未获取到题目 [{args.slug}] 的提交记录。")
        return

    # 按时间正序排列（最早 -> 最新）
    chronological = list(reversed(submissions))[:args.limit]
    print(f"[+] 成功获取题目 [{args.slug}] 的 {len(chronological)} 条提交记录！\n")

    for idx, sub in enumerate(chronological, 1):
        sub_id = sub["id"]
        status = sub.get("status_display")
        time_ago = sub.get("time")
        timestamp = sub.get("timestamp")
        time_str = datetime.fromtimestamp(timestamp).strftime("%Y-%m-%d %H:%M:%S") if timestamp else time_ago
        status_emoji = "✅" if status == "Accepted" else "❌"

        detail = get_submission_detail(sub_id, cookie)
        code = detail.get("code") if detail else "(无法拉取代码)"
        runtime_display = detail.get("runtimeDisplay") if detail and detail.get("runtimeDisplay") else sub.get("runtime", "N/A")
        memory_display = detail.get("memoryDisplay") if detail and detail.get("memoryDisplay") else sub.get("memory", "N/A")
        runtime_pct = detail.get("runtimePercentile") if detail else None
        memory_pct = detail.get("memoryPercentile") if detail else None

        perf_summary = f"运行时间: {runtime_display}"
        if runtime_pct is not None:
            perf_summary += f" (击败 {runtime_pct:.2f}%)"
        perf_summary += f" | 内存: {memory_display}"
        if memory_pct is not None:
            perf_summary += f" (击败 {memory_pct:.2f}%)"

        print(f"[{idx}] 提交 ID: {sub_id} | 状态: {status_emoji} {status:<15} | 时间: {time_str}")
        print(f"    ├─ ⚡ 性能指标: {perf_summary}")

        if args.outdir:
            os.makedirs(args.outdir, exist_ok=True)
            status_clean = status.replace(" ", "_")
            fname = f"{idx:02d}_{sub_id}_{status_clean}.cpp"
            fpath = os.path.join(args.outdir, fname)
            with open(fpath, "w", encoding="utf-8") as f:
                f.write(f"// 提交编号: {sub_id}\n")
                f.write(f"// 提交时间: {time_str}\n")
                f.write(f"// 判题结果: {status}\n")
                f.write(f"// {perf_summary}\n\n")
                f.write(code)
            print(f"    └─ 📁 已保存到: {fpath}")
        else:
            print("    代码前 5 行预览:")
            for l in code.splitlines()[:5]:
                print(f"       {l}")
            print()


if __name__ == "__main__":
    main()
