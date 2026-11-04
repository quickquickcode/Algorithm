// 提交编号: 758575948
// 提交时间: 2026-11-04 16:00:00
// 判题结果: Compile Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    bool isAnagram(string s, string t) {
        int s_nums[26]={};
        int[26] t_nums=[];
        for(int i=0li<s.length();i++){
            s_nums[(int)s[i]-'a']++;
            t_nums[(int)t[i]-'a']++;
        }
        for(int i=0;i<26;i++){
            if(s_nums[i]!=t_nums[i]) return false;
        }
        return true;
    }
};