// 提交编号: 760881573
// 提交时间: 2026-11-20 15:20:13
// 判题结果: Wrong Answer
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        for(int i=0;i<(k)%nums.size();i++){
            int temp = nums[0];
            nums.erase(nums.begin()+0);
            nums.push_back(temp);
        }

    }
};