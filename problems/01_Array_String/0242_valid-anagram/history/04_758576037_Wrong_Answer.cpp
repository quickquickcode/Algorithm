// 提交编号: 758576037
// 提交时间: 2026-11-04 16:00:20
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    bool isAnagram(string s, string t) {
        int s_nums[26]={};
        int t_nums[26]={};
        for(int i=0;i<s.length();i++){
            s_nums[(int)s[i]-'a']++;
            t_nums[(int)t[i]-'a']++;
        }
        for(int i=0;i<26;i++){
            if(s_nums[i]!=t_nums[i]) return false;
        }
        return true;
    }
};