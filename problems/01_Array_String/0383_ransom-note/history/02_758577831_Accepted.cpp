// 提交编号: 758577831
// 提交时间: 2026-11-04 16:07:24
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 12.5 MB (击败 5.05%)

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