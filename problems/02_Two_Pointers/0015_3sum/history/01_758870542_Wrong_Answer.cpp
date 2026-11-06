// 提交编号: 758870542
// 提交时间: 2026-11-06 12:24:24
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result={};
        for(int i=0;i<nums.size()-2;i++){
            for(int j=i+1;j<nums.size()-1;j++){
                for(int k=j+1;k<nums.size();k++){
                    if(nums[i]+nums[j]+nums[k]==0){
                        vector<int> temp = {nums[i],nums[j],nums[k]};
                        result.push_back(temp);
                    }
                }
            }
        }
        return result;
    }
};