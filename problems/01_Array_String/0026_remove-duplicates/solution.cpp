// 26. 删除有序数组中的重复项
// 核心解法：快慢双指针（有序去重）
// 时间复杂度：O(N)，空间复杂度：O(1)
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int slow = 0; // slow 指向当前已确定的不重复有效序列的末尾
        int fast = 1; // fast 从下标 1 开始向前探路

        while (fast < nums.size()) {
            if (nums[slow] == nums[fast]) {
                // 遇到重复元素，探路者跳过
                fast++;
            } else {
                // 遇到新元素，放入 slow+1 位置，并推进 slow
                nums[slow + 1] = nums[fast];
                slow++;
                fast++;
            }
        }

        // slow 是末尾元素的下标，因此有效元素总个数为 slow + 1
        return slow + 1;
    }
};
