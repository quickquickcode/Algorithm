class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int p = 0;
        int left_sum = 0;

        int max=-1000000;
        while ( p < nums.size() ){
            if (left_sum<0) {
                left_sum=0;
            }
            left_sum += nums[p];
            if (left_sum>max){
                max=left_sum;
            }
            p++;
        }
        return max;
    }
};