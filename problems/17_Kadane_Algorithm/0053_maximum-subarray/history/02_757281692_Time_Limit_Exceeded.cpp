// 提交编号: 757281692
// 提交时间: 2026-10-27 20:03:35
// 判题结果: Time Limit Exceeded
// 运行时间: N/A | 内存: N/A

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int p = 0, q = nums.size()-1;
        int left_sum = 0;
        int max=0;
        while ( p < nums.size() ){
            left_sum += nums[p];
            if (left_sum<0) {
                left_sum=0;
                p++;
            }
            if (left_sum>max){
                max=left_sum;
            }
        }
        return max;
    }
};