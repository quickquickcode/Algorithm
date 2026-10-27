// 解法二：双向对撞双指针（元素最少移动，适合删除元素较少的情况）
// 时间复杂度：O(N)，空间复杂度：O(1)
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0;
        int right = nums.size() - 1;

        // 必须使用 <=，因为当 left == right 时，相遇位置的元素仍需判断是否等于 val
        while (left <= right) {
            if (nums[left] == val) {
                // 将右边元素直接覆盖到左边当前位置
                nums[left] = nums[right];
                right--; // 右侧已消费，缩短搜索区间
                // 注意：此时 left 不能++，因为移过来的 nums[right] 本身可能也等于 val，需在下一轮复检
            } else {
                left++; // 当前位置合法，检查下一个
            }
        }

        // 循环结束时，区间 [0, left) 内全是有效元素，left 即为新长度
        return left;
    }
};
