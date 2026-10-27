// 提交编号: 757312118
// 提交时间: 2026-10-27 22:10:39
// 判题结果: Wrong Answer
// 运行时间: N/A | 内存: N/A

class Solution {
public:
    int trap(vector<int>& height) {
        int p=0;
        int max=-1;
        int sum=0;
        for(int i=0;i<height.size();i++){
            if(height[i]>max){
                max=height[i];
                p=i;
            }
        }
        max = -1;
        for(int i=0;i<p;i++){
            if(height[i]>max){
                max=height[i];
            }
            else{
                sum+=max-height[i];
            }
        }
        for(int i=height.size()-1; i>p; i--){
            if(height[i]>max){
                max=height[i];
            }
            else{
                sum+=max-height[i];
            }
        }
        return sum;
    }
};