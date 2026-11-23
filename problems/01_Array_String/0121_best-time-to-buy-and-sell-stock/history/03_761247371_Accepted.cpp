// 提交编号: 761247371
// 提交时间: 2026-11-23 16:27:36
// 判题结果: Accepted
// 运行时间: 2 ms (击败 39.85%) | 内存: 95 MB (击败 98.30%)

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
                min=prices[i];
            }
        }
        return max;
    }
};