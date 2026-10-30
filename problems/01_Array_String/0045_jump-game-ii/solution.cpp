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
        return nums[0];
    }
};