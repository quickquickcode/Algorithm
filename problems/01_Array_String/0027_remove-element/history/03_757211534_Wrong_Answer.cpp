// 提交编号: 757211534
// 提交时间: 2026-10-27 15:07:17
// 判题结果: Wrong Answer
// 运行时间: N/A | 内存: N/A

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size() - 1;
        int times = 0;
        while (left < right){
            if(nums[left] != val){
                left++;
                times++;
            }
            else{
                nums[left] = nums[right];
                right--;
            }
        }
        return times;
    }
};