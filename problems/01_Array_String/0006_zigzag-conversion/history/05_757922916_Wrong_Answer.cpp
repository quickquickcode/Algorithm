// 提交编号: 757922916
// 提交时间: 2026-10-31 17:26:35
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

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
            while(j<s.size()){
                result+=s[j];
                j = 2*(numRows-1)*(times+1)-j;
                times++;
            }
        }
        // int times=s.size()/
        return result;
    }
};