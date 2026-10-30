// 提交编号: 757749376
// 提交时间: 2026-10-30 13:11:08
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 8.2 MB (击败 64.37%)

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