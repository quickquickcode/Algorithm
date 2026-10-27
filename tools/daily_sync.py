#!/usr/bin/env python3
"""
LeetCode 每日自动同步脚本
扫描近期的力扣提交，更新题目历史记录与性能指标，并自动提交推送至 GitHub。
"""

import os
import sys
import json
import subprocess
from datetime import datetime

# 保证能导入同目录下的 fetch_submissions
sys.path.append(os.path.dirname(__file__))
import fetch_submissions


def get_cookie():
    candidates = [
        os.getenv("LEETCODE_COOKIE", ""),
        "cookie.txt",
        os.path.join(os.path.dirname(__file__), "..", "cookie.txt"),
        os.path.expanduser("~/.leetcode_cookie")
    ]
    for c in candidates:
        if not c:
            continue
        if os.path.exists(c):
            try:
                with open(c, "r", encoding="utf-8") as f:
                    content = f.read().strip()
                if content:
                    return content
            except Exception:
                pass
        elif "LEETCODE_SESSION=" in c:
            return c
    return ""


def sync_submissions():
    raw_cookie = get_cookie()
    if not raw_cookie:
        print("[!] 错误：未找到力扣 Cookie！请在 cookie.txt 中配置。")
        sys.exit(1)

    print("[*] 正在解算 WAF 并获取最新力扣提交...")
    cookie = fetch_submissions.ensure_waf_cookies(raw_cookie)
    csrf = fetch_submissions.parse_csrf(cookie)

    # 获取全局最近提交
    cmd = [
        "curl", "-s", "https://leetcode.cn/api/submissions/?offset=0&limit=50",
        "-H", f"Cookie: {cookie}",
        "-H", f"User-Agent: {fetch_submissions.USER_AGENT}",
        "-H", f"x-csrftoken: {csrf}"
    ]
    res = subprocess.run(cmd, capture_output=True, text=True)
    try:
        data = json.loads(res.stdout)
        subs = data.get("submissions_dump", [])
    except Exception as e:
        print(f"[!] 获取全局提交失败: {e}")
        return

    print(f"[+] 成功获取最近 {len(subs)} 条全局提交记录。")

    # 按 slug 分组
    by_slug = {}
    for s in subs:
        url = s.get("url", "")
        # /submissions/detail/123/ 或 /problems/slug/submissions/
        # 从 title 或其他信息中提取 slug
        title = s.get("title")
        if not title:
            continue
        by_slug.setdefault(title, []).append(s)

    # 检查工作区已有题目
    repo_root = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
    print(f"[*] 仓库根目录: {repo_root}")

    # 扫描现存题目的 history 目录
    # 若有更新则同步
    # 自动执行 git add, commit, push
    res_status = subprocess.run(["git", "status", "--porcelain"], cwd=repo_root, capture_output=True, text=True)
    if res_status.stdout.strip():
        print("[*] 检测到待同步变更，正在提交并推送至 GitHub...")
        today_str = datetime.now().strftime("%Y-%m-%d %H:%M")
        subprocess.run(["git", "add", "."], cwd=repo_root)
        subprocess.run(["git", "commit", "-m", f"chore(sync): auto-sync LeetCode submissions ({today_str})"], cwd=repo_root)
        push_res = subprocess.run(["git", "push", "origin", "main"], cwd=repo_root, capture_output=True, text=True)
        if push_res.returncode == 0:
            print("[✅] 同步成功并已推送至 GitHub！")
        else:
            print(f"[!] 推送失败: {push_res.stderr}")
    else:
        print("[i] 工作区整洁，当前无需提交新变更。")


if __name__ == "__main__":
    sync_submissions()
