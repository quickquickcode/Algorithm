// 提交编号: 758799620
// 提交时间: 2026-11-05 20:48:41
// 判题结果: Compile Error
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
                if(start==end){
                    string temp=std::to_string(start);
                }
                else{
                    string temp=std::to_string(start)+"->"+std::to_string(end);
                }
                start=nums[i];
                end=start;
                result.push_back(temp);
            }
        }
        if(start==end){
            string temp=std::to_string(start);
        }
        else{
            string temp=std::to_string(start)+"->"+std::to_string(end);
        }
        return result; 
    }
};