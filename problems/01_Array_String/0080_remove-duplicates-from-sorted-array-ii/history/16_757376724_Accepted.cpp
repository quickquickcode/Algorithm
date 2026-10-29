// 提交编号: 757376724
// 提交时间: 2026-10-28 11:34:54
// 判题结果: Accepted
// 运行时间: 4 ms (击败 92.40%) | 内存: 19.1 MB (击败 71.40%)

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size()<2){
            return nums.size();
        }
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
        return slow+2;
    }
};