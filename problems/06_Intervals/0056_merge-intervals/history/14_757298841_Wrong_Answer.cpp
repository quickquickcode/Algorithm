// 提交编号: 757298841
// 提交时间: 2026-10-27 21:13:55
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

                int a=intervals[i][0];
                int b=intervals[i][1];
                int c=intervals[j][0];
                int d=intervals[j][1];

                if(b>=c | d>=a ){
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
        return intervals;
    }
};