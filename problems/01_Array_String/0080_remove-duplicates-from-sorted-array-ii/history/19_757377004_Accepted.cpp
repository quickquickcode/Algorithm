// 提交编号: 757377004
// 提交时间: 2026-10-28 11:36:08
// 判题结果: Accepted
// 运行时间: 13 ms (击败 26.84%) | 内存: 19.3 MB (击败 29.62%)

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size()<2){
            return nums.size();
        }
        int slow = 0, fast = 2;
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
        return slow+2;
    }
};