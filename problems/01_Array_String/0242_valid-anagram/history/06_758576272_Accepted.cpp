// 提交编号: 758576272
// 提交时间: 2026-11-04 16:01:14
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 9.6 MB (击败 36.84%)

class Solution {
public:
    bool isAnagram(string s, string t) {
        int s_nums[26]={};
        int t_nums[26]={};
        for(int i=0;i<s.length();i++){
            s_nums[(int)s[i]-'a']++;
        }
        for(int i=0;i<t.length();i++){
            t_nums[(int)t[i]-'a']++;
        }
        for(int i=0;i<26;i++){
            if(s_nums[i]!=t_nums[i]) return false;
        }
        return true;
    }
};