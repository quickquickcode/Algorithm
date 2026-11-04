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