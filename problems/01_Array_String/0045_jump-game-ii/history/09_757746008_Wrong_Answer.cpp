// 提交编号: 757746008
// 提交时间: 2026-10-30 12:30:28
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int jump(vector<int>& nums) {
        int p = nums.size()-1;
        if(!p){
            return 0;
        }
        nums[p]=0;
        for (int i = p-1; i>=0; i--){
            int min=10000;
            if(nums[i]){
                for(int j=1; j<=nums[i] && i+j<nums.size();j++ ){
                    min=std::min(min,nums[i+j]+1);
                }
            }
            nums[i]=min;
        }
        return nums[0]-1;
    }
};