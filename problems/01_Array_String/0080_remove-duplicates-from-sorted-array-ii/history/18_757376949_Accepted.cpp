// 提交编号: 757376949
// 提交时间: 2026-10-28 11:35:55
// 判题结果: Accepted
// 运行时间: 10 ms (击败 50.28%) | 内存: 19.1 MB (击败 84.70%)

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len=nums.size();
        if (len<2){
            return len;
        }
        int slow = 0, fast = 2;
        while (fast < len){
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