// 提交编号: 757217281
// 提交时间: 2026-10-27 15:27:59
// 判题结果: Compile Error
// 运行时间: N/A | 内存: N/A

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0， fast = 1；
        while (fast < nums.size()){
            if (nums[slow] == fast){
                fast++;
            }
            else{
                nums[slow+1]=nums[fast];
                fast++;
                slow++;
            }
        } 
    }
};