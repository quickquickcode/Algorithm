// 提交编号: 757922279
// 提交时间: 2026-10-31 17:22:30
// 判题结果: Compile Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    string convert(string s, int numRows) {
        string result="";
        // result+=s[0];

        for (int i=0;i<numRows;i++){
            int j=i;
            while(j<s.size()){
                result+=s[j];
                j = 2(n-1)*(i+1)-j;
            }
        }
        // int times=s.size()/
        return result;
    }
};