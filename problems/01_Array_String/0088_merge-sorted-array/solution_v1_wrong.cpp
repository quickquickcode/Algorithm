// 错误尝试版本 1：前向插入 + 迭代器与下标混淆
// 来源：实战刷题过程记录
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int x = 0, y = 0;
        for (int i = 0; i < m + n; i++) {
            // ❌ 错误 1：operator[] 接收整数下标，而不是迭代器 nums1.begin() + x
            // ❌ 错误 2：insert 第二个参数类型错误，且括号不匹配
            if (nums1[nums1.begin() + x] > nums2[nums2.begin() + y]) {
                nums1.insert(nums1.begin() + x, nums2[nums2.begin() + y]));
                nums1.pop_back();
            }
            // ❌ 错误 3：y 没有递增，导致同一元素可能反复比较
            // ❌ 错误 4：<= 的情况完全没有推进 x，循环空转
            // ❌ 错误 5：循环次数固定为 m+n，当数组耗尽时访问越界
            // ❌ 错误 6：insert 单次复杂度 O(N)，整体退化为 O(N^2)
        }
    }
};
