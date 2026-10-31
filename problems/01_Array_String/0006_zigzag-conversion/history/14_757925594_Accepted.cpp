// 提交编号: 757925594
// 提交时间: 2026-10-31 17:44:38
// 判题结果: Accepted
// 运行时间: 4 ms (击败 64.82%) | 内存: 10.9 MB (击败 78.50%)

class Solution {
public:
    string convert(string s, int numRows) {
        string result="";
        // result+=s[0];
        if(numRows==1){
            return s;
        }
        for (int i=0;i<numRows;i++){
            int j=i;
            int times=0;
            int jiao=0;
            while(j<s.size()){
                result+=s[j];
                j = 2*(numRows-1)*(times+1)-j;
                if(j==2*(numRows-1)*(times+1)-j){
                    times++;
                    j=2*(numRows-1)*(times+1)-j;
                }
                times++;
            }
        }
        // int times=s.size()/
        return result;
    }
};

