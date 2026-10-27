// 错误尝试版本：左右对撞交换，内层无界越界 + 返回值与计数逻辑混淆
// 来源：实战刷题过程记录
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int x = 0, y = nums.size() - 1;
        int sum = 0;
        while (x < y) {
            int t = 0;
            // ❌ 错误 1：内层 while 无边界检查！若没找到 val，x 会一路递增导致 nums[x] 越界崩溃
            while (nums[x] != val) {
                x++;
            }
            // ❌ 错误 2：内层 while 无边界检查！若全是 val，y 会减到 -1 访问 nums[-1] 越界
            while (nums[y] == val) {
                y--;
            }
            t++;
            if (x < y) {
                int temp = nums[y];
                nums[y] = nums[x];
                nums[x] = temp;
                // ❌ 错误 3：t 与 sum 的累加逻辑完全混乱，既不是元素计数也不是有效位指针
                sum += t;
            }
        }
        // ❌ 错误 4：多余且有害的 resize，一旦 sum 算错直接截断失误
        nums.resize(nums.size() - sum);
        // ❌ 错误 5：题目要求返回保留下来的元素个数 k，而非移除的数量 sum
        return sum;
    }
};
