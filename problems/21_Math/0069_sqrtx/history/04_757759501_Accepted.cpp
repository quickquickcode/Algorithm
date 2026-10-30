// 提交编号: 757759501
// 提交时间: 2026-10-30 14:29:31
// 判题结果: Accepted
// 运行时间: 39 ms (击败 5.19%) | 内存: 8.3 MB (击败 85.91%)

class Solution {
public:
    int mySqrt(int x) {
        double result=0;
        while(result*result<=x){
            result++;
        }
        return result-1;
    }
};