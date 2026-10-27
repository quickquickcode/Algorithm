// 错误尝试版本 3：双指针结构正确，但变量下标发生交叉赋值
// 来源：实战刷题过程记录
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p = m - 1, q = n - 1;
        int x = m + n - 1;
        while (q >= 0) {
            if (p >= 0 && nums1[p] > nums2[q]) {
                // ❌ 错误 1：逻辑判断 nums1[p] 较大，却错误赋值了 nums2[p]！用 p 索引 nums2 还会越界
                nums1[x] = nums2[p]; 
                x--;
                p--;
            }
            else {
                // ❌ 错误 2：else 分支应取 nums2[q]，却错误写成了 nums1[q]！
                nums1[x] = nums1[q]; 
                x--;
                q--;
            }
        }
    }
};
