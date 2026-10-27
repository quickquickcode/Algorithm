// 42. 接雨水 (Trapping Rain Water) - Hard 困难
// 核心解法：最高峰拆分法 / 双向扫描法
// 时间复杂度：O(N)，空间复杂度：O(1)
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;

        // 1. 寻找全局最高峰的位置 p
        int p = 0;
        int max_val = -1;
        for (int i = 0; i < height.size(); i++) {
            if (height[i] > max_val) {
                max_val = height[i];
                p = i;
            }
        }

        int sum = 0;

        // 2. 从左向最高峰扫描：由于右侧有全局最高峰挡着，当前柱子能接的水仅取决于左侧历史最高点
        max_val = -1;
        for (int i = 0; i < p; i++) {
            if (height[i] > max_val) {
                max_val = height[i];
            } else {
                sum += max_val - height[i];
            }
        }

        // 3. 从右向最高峰扫描：同理，左侧有最高峰挡着，当前柱子能接的水仅取决于右侧历史最高点
        max_val = -1; // 必须重置！
        for (int i = height.size() - 1; i > p; i--) {
            if (height[i] > max_val) {
                max_val = height[i];
            } else {
                sum += max_val - height[i];
            }
        }

        return sum;
    }
};
