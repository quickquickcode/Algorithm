class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min=prices[0],sum=0;
        for(int i = 0; i<prices.size();i++){
            if(prices[i]<min){
                min=prices[i];
            }
            else{
                sum+=prices[i]-min;
                min=prices[i];
            }
        }
        return sum;
    }
};