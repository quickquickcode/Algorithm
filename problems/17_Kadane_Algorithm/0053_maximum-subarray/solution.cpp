// 53. 最大子数组和 (Maximum Subarray)
// 解法：Kadane 算法 / 贪心在线处理
// 时间复杂度：O(N)，空间复杂度：O(1)
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // left_sum: 以当前元素结尾的最大子数组和
        int left_sum = 0;
        // max_val: 全局最大子数组和。初始化必须能兼容全负数数组（如 INT_MIN 或 nums[0]）
        int max_val = INT_MIN;

        for (int x : nums) {
            // 核心贪心准则：如果之前的累计和为负数，对后续求和只会产生负收益，果断断舍离重置为 0
            if (left_sum < 0) {
                left_sum = 0;
            }
            left_sum += x;
            if (left_sum > max_val) {
                max_val = left_sum;
            }
        }

        return max_val;
    }
};
