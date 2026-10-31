// 提交编号: 757916295
// 提交时间: 2026-10-31 16:49:14
// 判题结果: Compile Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int romanToInt(string s) {
        int last=0;
        int sum=0;
        for (int i=0;i<s.len();i++){
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