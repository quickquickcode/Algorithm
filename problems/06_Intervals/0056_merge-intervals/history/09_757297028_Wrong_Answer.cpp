// 提交编号: 757297028
// 提交时间: 2026-10-27 21:05:59
// 判题结果: Wrong Answer
// 运行时间: N/A | 内存: N/A

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> v{};    
        int i=0;
        while(i<intervals.size()){
            int j=i+1;
            int t=0;
            while(j<intervals.size()){
                if(intervals[i][1]>=intervals[j][0]){
                    intervals[j][0]=intervals[i][0];
                    t++;
                }
                if(intervals[j][1]>=intervals[i][0]){
                    intervals[j][1]=intervals[j][1];
                    t++;
                }
                j++;
            }
            if(t>0){
                intervals.erase(intervals.begin()+i);
            }
            else{
                i++;
            }
            // i++;
        }
        return intervals;
    }
};