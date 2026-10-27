// 提交编号: 757210894
// 提交时间: 2026-10-27 15:04:53
// 判题结果: Wrong Answer
// 运行时间: N/A | 内存: N/A

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size() - 1;
        int times = 0;
        while (left < right){
            while(left < nums.size() - 1 && nums[left] != val){
                left++;
                times++;
            }
            nums[left] = nums[right];
            nums[right] = 0;
            right--;
        }
        return times;
    }
};