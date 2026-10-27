// 错误尝试版本 2：逆向双指针，但比较方向颠倒 + 无边界防护
// 来源：实战刷题过程记录
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p = m - 1, q = n - 1;
        int x = m + n - 1;
        for (int i = 0; i < m + n; i++) {
            // ❌ 错误 1：逻辑颠倒！从后往前填，末尾应该放【较大】的元素，这里却把较小的赋给了末尾
            if (nums1[p] > nums2[q]) {
                nums1[x] = nums2[q];
                x--;
                q--;
            }
            // ❌ 错误 2：写成独立的 if，且没有检查 p >= 0 和 q >= 0
            // 当某个数组耗尽后，访问 nums1[-1] 或 nums2[-1] 触发段错误
            if (nums1[p] <= nums2[q]) {
                nums1[x] = nums1[p];
                x--;
                p--;
            }
        }
    }
};
