// 提交编号: 757691999
// 提交时间: 2026-10-29 22:42:58
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 19.6 MB (击败 82.98%)

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min=prices[0],max=0,sum=0;
        for(int i = 0; i<prices.size();i++){
            if(prices[i]<min){
                min=std::min(prices[i],min);
            }
            else{
                sum+=prices[i]-min;
                min=prices[i];
            }

        }
        return sum;
    }
};