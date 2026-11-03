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