// 提交编号: 757748486
// 提交时间: 2026-10-30 13:00:41
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    bool isHappy(int n) {
        vector<int> list={};
        int sum;
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