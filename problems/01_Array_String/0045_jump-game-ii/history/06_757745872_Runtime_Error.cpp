// 提交编号: 757745872
// 提交时间: 2026-10-30 12:28:37
// 判题结果: Runtime Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int jump(vector<int>& nums) {
        int p = nums.size()-1;
        if(!p){
            return 0;
        }
        nums[p]=0;
        for (int i = p; i>=0; i--){
            int min=10000;
            if(nums[i]){
                for(int j=0; j<=nums[i];j++ ){
                    min=std::min(min,nums[i+j]+1);
                }
            }
            nums[i]=min;
        }
        return nums[0]-1;
    }
};