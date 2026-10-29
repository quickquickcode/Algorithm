// 提交编号: 757227548
// 提交时间: 2026-10-27 16:04:18
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0, times = 0, fast = 0;
        while (fast < nums.size()){
            if (nums[slow] == nums[fast]){
                fast++;
                times++;
            }
            else{
                slow=fast;
                times=0;
            }
            if (times >=2 ){
                nums.erase(nums.begin() + fast);
            }
        }
        return slow;
    }
};