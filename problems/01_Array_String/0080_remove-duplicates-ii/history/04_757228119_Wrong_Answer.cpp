// 提交编号: 757228119
// 提交时间: 2026-10-27 16:06:20
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0, times = 0, fast = 0;
        while (fast < nums.size()){
            if (nums[slow] == nums[fast]){
                times++;
                if (times >=2 ){
                    nums.erase(nums.begin() + fast);
                }
                else{
                    fast++;
                }
            }
            else{
                slow=fast;
                times=0;
            }

        }
        return slow;
    }
};