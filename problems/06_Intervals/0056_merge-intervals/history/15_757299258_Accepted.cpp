// 提交编号: 757299258
// 提交时间: 2026-10-27 21:15:41
// 判题结果: Accepted
// 运行时间: 2075 ms | 内存: 22.9 MB

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
        return intervals;
    }
};