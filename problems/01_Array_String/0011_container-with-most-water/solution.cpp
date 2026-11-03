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