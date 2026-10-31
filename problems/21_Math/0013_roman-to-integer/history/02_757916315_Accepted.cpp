// 提交编号: 757916315
// 提交时间: 2026-10-31 16:49:21
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 9.9 MB (击败 88.54%)

class Solution {
public:
    int romanToInt(string s) {
        int last=0;
        int sum=0;
        for (int i=0;i<s.size();i++){
            switch(s[i]){
                case('I'):
                    last=1;
                    sum+=last;
                    break;
                case('V'):
                    if(last==1){
                        sum-=2*last;
                    }
                    last=5;
                    sum+=last;
                    break;
                case('X'):
                    if(last==1){
                        sum-=2*last;
                    }
                    last=10;
                    sum+=last;
                    break;
                case('L'):
                    if(last==10){
                        sum-=2*last;
                    }
                    last=50;
                    sum+=last;
                    break;
                case('C'):
                    if(last==10){
                        sum-=2*last;
                    }
                    last=100;
                    sum+=last;
                    break;
                case('D'):
                    if(last==100){
                        sum-=2*last;
                    }
                    last=500;
                    sum+=last;
                    break;
                case('M'):
                    if(last==100){
                        sum-=2*last;
                    }
                    last=1000;
                    sum+=last;
                    break;
            }
        }
        return sum;

    }
};