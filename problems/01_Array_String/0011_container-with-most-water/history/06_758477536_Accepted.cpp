// 提交编号: 758477536
// 提交时间: 2026-11-03 22:16:58
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 61.4 MB (击败 90.53%)

class Solution {
public:
    int maxArea(vector<int>& height) {
        int max=0;
        int i=0,j=height.size()-1;
        int i_max=0, j_max=0;
        while(i<j){
            int water=std::min(height[i],height[j]) * (j-i);
            max=std::max(max, water);
            i_max = std::max(i_max,  height[i]);
            j_max = std::max(j_max,  height[j]);

            if(i_max<=j_max){
                while(i_max >= height[i] && i<height.size()-1){
                    i++;
                }
            }
            else{
                while(j_max >= height[j] && j>0){
                    j--;
                }
            }
        }

        return max;
    }
};