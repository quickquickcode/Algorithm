// 提交编号: 761267930
// 提交时间: 2026-11-23 18:20:17
// 判题结果: Accepted
// 运行时间: 650 ms (击败 5.01%) | 内存: 51.1 MB (击败 78.10%)

class Solution {
public:
    bool canJump(vector<int>& nums) {
        nums[nums.size()-1]=1;
        for(int i=nums.size()-2;i>=0;i--){
            int temp=0;
            for(int j=1;j<=nums[i]&&(i+j)<nums.size();j++){
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