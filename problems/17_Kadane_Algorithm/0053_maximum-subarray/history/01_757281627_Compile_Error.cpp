// 提交编号: 757281627
// 提交时间: 2026-10-27 20:03:20
// 判题结果: Compile Error
// 运行时间: N/A | 内存: N/A

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int p = 0, q = ums.size()-1;
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