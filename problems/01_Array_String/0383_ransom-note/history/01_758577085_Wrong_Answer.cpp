// 提交编号: 758577085
// 提交时间: 2026-11-04 16:04:18
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

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
            if(s_nums[i]){
                if(!t_nums[i]){
                    return false;
                }
            } 
        }
        return true;
    }
};