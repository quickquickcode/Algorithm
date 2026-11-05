// 提交编号: 758800288
// 提交时间: 2026-11-05 20:52:08
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 9.2 MB (击败 13.60%)

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
            else if ((double)nums[i]-end==1){
                end++;
            }
            else {
                string temp;
                if(start==end){
                    temp=std::to_string(start);
                }
                else{
                    temp=std::to_string(start)+"->"+std::to_string(end);
                }
                start=nums[i];
                end=start;
                result.push_back(temp);
            }
        }
        if(nums.size()){
        string temp;
        if(start==end){
            temp=std::to_string(start);
        }
        else{
            temp=std::to_string(start)+"->"+std::to_string(end);
        }
        result.push_back(temp);
        }

        return result; 
    }
};