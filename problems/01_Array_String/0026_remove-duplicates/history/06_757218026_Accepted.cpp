// 提交编号: 757218026
// 提交时间: 2026-10-27 15:30:37
// 判题结果: Accepted
// 运行时间: 0 ms | 内存: 22.1 MB

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
        return slow+1;
    }
};