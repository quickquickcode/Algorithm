// 提交编号: 758550460
// 提交时间: 2026-11-04 14:05:41
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result={};
        result.push_back(nums[0]);
        int right=1;
        for(int i=1;i<nums.size();i++){
            result.push_back(nums[i]*result[i-1]);
        }
        for(int i=result.size()-1;i>0;i--){
            result[i]=result[i-1]*right;
            right*=nums[i];
        }
        result[0]*=right;
        return result;
    }
};