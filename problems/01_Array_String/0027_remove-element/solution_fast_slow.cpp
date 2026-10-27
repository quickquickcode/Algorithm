// 解法一：快慢指针法（最推荐，简单不易出错）
// 时间复杂度：O(N)，空间复杂度：O(1)
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0; // 指向下一个有效元素需要存放的坑位

        // fast 作为探路者，遍历所有元素
        for (int fast = 0; fast < nums.size(); ++fast) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow++;
            }
        }

        // slow 即为所有不等于 val 的有效元素个数
        return slow;
    }
};
