// 提交编号: 760880977
// 提交时间: 2026-11-20 15:16:49
// 判题结果: Compile Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        for(int i=0;i<k;i++){
            int temp = nums[0];
            nums.erase(0);
            nums.push_back(temp);
        }

    }
};