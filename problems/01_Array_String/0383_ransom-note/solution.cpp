class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int s_nums[26]={};
        int t_nums[26]={};
        for(int i=0;i<ransomNote.length();i++){
            s_nums[(int)ransomNote[i]-'a']++;
        }
        for(int i=0;i<magazine.length();i++){
            t_nums[(int)magazine[i]-'a']++;
        }
        for(int i=0;i<26;i++){
            if(s_nums[i]>t_nums[i]){                
                return false;
            } 
        }
        return true;
    }
};