// 提交编号: 758473998
// 提交时间: 2026-11-03 22:00:31
// 判题结果: Time Limit Exceeded
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int maxArea(vector<int>& height) {
        int max=0;
        for(int i=0;i<height.size();i++){
            for(int j=i+1;j<height.size();j++){
                int water=std::min(height[i],height[j]) * (j-i);
                max=std::max(max, water);
            }
        }
        return max;
    }

};