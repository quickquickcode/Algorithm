// 提交编号: 758816468
// 提交时间: 2026-11-05 22:21:59
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        vector<vector<int>> v{};
        vector<vector<int>> intervals=points;
        int i=0;
        while(i<intervals.size()){
            int j=i+1;
            int t=0;
            while(j<intervals.size()){

                int a=intervals[i][0];
                int b=intervals[i][1];
                int c=intervals[j][0];
                int d=intervals[j][1];

                if( (b>=c && c>=a) | (d>=a && a>=c) ){
                    intervals[j][0]=std::min({a,b,c,d});
                    intervals[j][1]=std::max({a,b,c,d});
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
        return intervals.size()+1;
    }
};