// 提交编号: 757295320
// 提交时间: 2026-10-27 20:58:52
// 判题结果: Compile Error
// 运行时间: N/A | 内存: N/A

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> v{};    
        int i=0;
        while(i<intervals.size()){
            int j=i+1;
            while(j<intervals.size()){
                int t=0;
                if(intervals[i][1]>=intervals[j][0]){
                    intervals[j][0]=intervals[i][0];
                    t++;
                }
                if(intervals[j][1]>=intervals[i][0]){
                    intervals[j][1]=intervals[j][1];
                    t++;
                }
                if(t){
                    intervals.erase(i);
                }
                else{
                    i++;
                    j++;
                }
            }
        return intervals;
        }
    }
};