class Solution {
public:
    bool isHappy(int n) {
        vector<int> list={};
        int sum=0;
        while(n!=1){
            while(n){
                int temp=n%10;
                n=n/10;
                sum+=temp*temp;
            }
            for(int i=0;i<list.size();i++){
                if(sum==list[i]){
                    return false;
                }
            }
            list.push_back(sum);
            n=sum;
            sum=0;
        }
        return true;
    }
};