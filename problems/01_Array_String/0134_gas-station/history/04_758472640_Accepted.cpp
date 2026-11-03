// 提交编号: 758472640
// 提交时间: 2026-11-03 21:54:35
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 110.1 MB (击败 38.31%)

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int use=0, foel=0;
        for(int i=0;i<gas.size();i++){
            use+=cost[i];
            foel+=gas[i];
        }
        if (use>foel){
            return -1;
        }
        foel=0;
        int p=0;
        for(int i=0;i<gas.size();i++){
            foel = foel + gas[i] - cost[i];
            if(foel<0){
                foel=0;
                p=i+1;
            }
        }
        return p;
    }
};