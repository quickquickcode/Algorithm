// 提交编号: 761247310
// 提交时间: 2026-11-23 16:27:20
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min = prices[0];
        int max = 0;
        for (int i=0;i<prices.size();i++){
            if((prices[i]-min)>max){
                max=prices[i]-min;
            }
            if(prices[i]<min){
                min=prices[i]-min;
            }
        }
        return max;
    }
};