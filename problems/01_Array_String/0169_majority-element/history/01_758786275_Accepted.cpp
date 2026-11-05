// 提交编号: 758786275
// 提交时间: 2026-11-05 19:36:03
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 41.1 MB (击败 38.53%)

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // 很久之前偷看过答案
        int times=0;
        int result=nums[0];
        for(int i=0;i<nums.size();i++){
            if(result==nums[i]){
                times++;
            }
            else{
                times--;
                if(times<0){
                    times=0;
                    result=nums[i];
                }
            }
        }
        return result;
    }
};