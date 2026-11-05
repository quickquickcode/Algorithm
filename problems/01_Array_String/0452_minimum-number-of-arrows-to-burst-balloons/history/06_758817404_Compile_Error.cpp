// 提交编号: 758817404
// 提交时间: 2026-11-05 22:28:04
// 判题结果: Compile Error
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

                if(b>=c && c>=a){
                    intervals[j][0]=std::min({b,c});
                    intervals[j][1]=std::max({b,c});
                    t++;
                }
                else if( d>=a && a>=c){
                    intervals[j][0]=std::min({a,d});
                    intervals[j][1]=std::max({a,d});
                    t++;
                }
                }

                j++;
            }
            if(t>0){
                intervals.erase(intervals.begin()+i);
            }
            else{
                i++;
            }
        }
        return intervals.size();
    }
};