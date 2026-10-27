// [120. Triangle] 三角形最小路径和
// 力扣链接: https://leetcode.cn/problems/triangle/

#include <vector>
#include <algorithm>

using namespace std;

// ========================================================
// 标杆解法：自底向上 原地动态规划 (Bottom-up In-place DP)
// 时间复杂度: O(N^2) 三角形元素总个数为 N(N+1)/2，每个元素访问一次
// 空间复杂度: O(1) 原地复用 triangle 数组，无额外堆栈分配
// 实际测评: 0 ms (击败 100.00%) | 12.2 MB (击败 97.91%)
// ========================================================
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int depth = triangle.size();
        // 从倒数第二行自底向上收敛，规避边界特判
        for (int i = depth - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
            }
        }
        return triangle[0][0];
    }
};
