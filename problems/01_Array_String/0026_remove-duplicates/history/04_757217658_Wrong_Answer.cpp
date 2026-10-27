// 提交编号: 757217658
// 提交时间: 2026-10-27 15:29:15
// 判题结果: Wrong Answer
// 运行时间: N/A | 内存: N/A

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0, fast = 1;
        while (fast < nums.size()){
            if (nums[slow] == nums[fast]){
                fast++;
            }
            else{
                nums[slow+1]=nums[fast];
                fast++;
                slow++;
            }
        } 
        return slow;
    }
};