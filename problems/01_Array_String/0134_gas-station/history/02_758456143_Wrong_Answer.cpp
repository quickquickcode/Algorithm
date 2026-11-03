// 提交编号: 758456143
// 提交时间: 2026-11-03 20:44:50
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int use=0, foel=0;
        for(int i=0;i<gas.size();i++){
            use+=cost[i];
            foel+=gas[i];
            gas[i]-=cost[i];
        }
        if (use>foel){
            return -1;
        }

        return 0;
    }
};