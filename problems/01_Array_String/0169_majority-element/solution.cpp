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