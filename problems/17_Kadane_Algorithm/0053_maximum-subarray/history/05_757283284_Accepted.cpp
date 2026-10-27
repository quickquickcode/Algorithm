// 提交编号: 757283284
// 提交时间: 2026-10-27 20:10:08
// 判题结果: Accepted
// 运行时间: 0 ms | 内存: 70.1 MB

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int p = 0;
        int left_sum = 0;
        int min = 0;
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