// 提交编号: 761245542
// 提交时间: 2026-11-23 16:19:29
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 70.1 MB (击败 70.92%)

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