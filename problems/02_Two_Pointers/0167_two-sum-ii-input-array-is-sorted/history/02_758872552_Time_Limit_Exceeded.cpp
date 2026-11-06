// 提交编号: 758872552
// 提交时间: 2026-11-06 12:49:48
// 判题结果: Time Limit Exceeded
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> result ={};
        for(int i=0;i<numbers.size()-1;i++){
            for(int j=i+1;j<numbers.size();j++){
                if(numbers[i]+numbers[j]==target){
                    result.push_back(i+1);
                    result.push_back(j+1);
                }
            }
        }
        return result;
    }
};