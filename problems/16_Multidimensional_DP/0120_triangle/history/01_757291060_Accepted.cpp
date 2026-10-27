// 提交编号: 757291060
// 提交时间: 2026-10-27 20:41:35
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 12.2 MB (击败 97.91%)

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int depth = triangle.size();
        for(int i = depth-2; i >= 0; i--){ //倒数第二行深度
            for(int j = 0; j <= i; j++){ //横向
                if(triangle[i+1][j]>triangle[i+1][j+1]){
                    triangle[i][j] += triangle[i+1][j+1];
                }
                else{
                    triangle[i][j] += triangle[i+1][j];
                }
            }
        }
        return triangle[0][0];
    }
};