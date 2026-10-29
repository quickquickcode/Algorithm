// 提交编号: 757376587
// 提交时间: 2026-10-28 11:34:21
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0, mid = slow + 2, fast = 2;
        while (fast < nums.size()){
            if (nums[slow] == nums[fast]){
                fast++;
            }
            else{
                nums[slow+2]=nums[fast];
                slow++;
                fast++;
            }
        }
        return slow;
    }
};