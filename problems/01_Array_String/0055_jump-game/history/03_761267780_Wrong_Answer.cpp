// 提交编号: 761267780
// 提交时间: 2026-11-23 18:19:08
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    bool canJump(vector<int>& nums) {
        nums[nums.size()-1]=1;
        for(int i=nums.size()-2;i>=0;i--){
            int temp=0;
            for(int j=0;j<nums[i]&&(i+j)<nums.size();j++){
                if (nums[i+j]){
                    temp++;
                }
            }
            nums[i]=temp;
        }
        if(nums[0]){
            return true;
        }
        else{
            return false;
        }
    }
};