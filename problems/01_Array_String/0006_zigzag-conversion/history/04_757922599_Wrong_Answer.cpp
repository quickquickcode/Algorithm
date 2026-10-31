// 提交编号: 757922599
// 提交时间: 2026-10-31 17:24:36
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    string convert(string s, int numRows) {
        string result="";
        // result+=s[0];

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