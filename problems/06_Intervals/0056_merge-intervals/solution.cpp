// 56. 合并区间 (Merge Intervals)
// 核心解法：按左端点排序 + 单遍流式合并
// 时间复杂度：O(N log N)，空间复杂度：O(log N) 或 O(N)（返回值与排序开销）
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        // 1. 核心关键：按左端点升序排序。这一步将二维空间重叠问题直接降维为一维！
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged;

        // 2. 线性扫描：类似于“传送带”收集器
        for (const auto& interval : intervals) {
            // 如果结果集为空，或者当前区间的左端点严格大于上一个区间的右端点，说明无重叠，直接放入
            if (merged.empty() || merged.back()[1] < interval[0]) {
                merged.push_back(interval);
            } else {
                // 有重叠：当前区间左端点必然 >= 上一区间左端点，因此只需将上一区间的右端点拉长
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }

        return merged;
    }
};
