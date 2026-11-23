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