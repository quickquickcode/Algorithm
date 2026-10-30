// 提交编号: 757745384
// 提交时间: 2026-10-30 12:22:37
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int jump(vector<int>& nums) {
        int p = nums.size()-1;
        nums[p]=0;
        for (int i = p; i>=0; i--){
            int min=1000;
            for(int j=0; j<nums[i];j++ ){
                min=std::min(min,nums[i+j]+1);
            }
            nums[i]=min;
        }
        return nums[0]-1;
    }
};