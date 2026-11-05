// 提交编号: 758798555
// 提交时间: 2026-11-05 20:42:40
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result={};
        int start=INT_MIN, end;
        int find_start=1;
        for(int i=0;i<nums.size();i++){
            if(find_start){
                start=nums[i];
                end=start;
                find_start=0;
            }
            else if (nums[i]-end==1){
                end++;
            }
            else {
                find_start=1;
                string temp=std::to_string(start)+"->"+std::to_string(end);
                result.push_back(temp);
            }
        }
        if(!find_start){
            string temp=std::to_string(start)+"->"+std::to_string(end);
            result.push_back(temp);
        }
        return result; 
    }
};