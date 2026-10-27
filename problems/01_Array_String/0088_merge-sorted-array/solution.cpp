// 标准解法：逆向双指针（从后向前填充）
// 时间复杂度：O(M + N)，空间复杂度：O(1)
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1;         // nums1 有效元素的末尾
        int p2 = n - 1;         // nums2 的末尾
        int tail = m + n - 1;   // 整体写入位置（从 nums1 物理空间末尾开始）

        // 核心心智模型：只要 nums2 还没放完，就持续挑选较大者填入 tail
        while (p2 >= 0) {
            if (p1 >= 0 && nums1[p1] > nums2[p2]) {
                nums1[tail--] = nums1[p1--];
            } else {
                nums1[tail--] = nums2[p2--];
            }
        }
        // 注意：当 p2 < 0 时循环结束；此时 nums1 剩余的元素本来就在正确位置，无需移动！
    }
};
