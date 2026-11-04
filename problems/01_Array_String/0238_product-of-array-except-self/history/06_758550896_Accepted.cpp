// 提交编号: 758550896
// 提交时间: 2026-11-04 14:08:29
// 判题结果: Accepted
// 运行时间: 7 ms (击败 19.52%) | 内存: 40.7 MB (击败 48.65%)

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
        result[0]=right;
        return result;
    }
};