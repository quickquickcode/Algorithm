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