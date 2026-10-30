// 提交编号: 757759399
// 提交时间: 2026-10-30 14:29:00
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int mySqrt(int x) {
        int result=0;
        while(result*result<x){
            result++;
        }
        return result-1;
    }
};