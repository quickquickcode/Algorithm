// 提交编号: 758477204
// 提交时间: 2026-11-03 22:15:24
// 判题结果: Compile Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    int maxArea(vector<int>& height) {
        int max=0;
        int i=0,j=height.szie()-1;
        int i_max=0, j_max=0;
        while(i<j){
            int water=std::min(height[i],height[j]) * (j-i);
            max=std::max(max, water);
            i_max = std::max(i_max,  height[i]);
            j_max = std::max(j_max,  height[j]);

            if(i_max<=j_max){
                while(i_max >= height[i] && i<height.size()){
                    i++;
                }
            }
            else{
                while(j_max >= height[j] && j>=0){
                    j--;
                }
            }
        }

        return max;
    }
};