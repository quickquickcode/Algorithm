// 提交编号: 757319183
// 提交时间: 2026-10-27 22:44:49
// 判题结果: Accepted
// 运行时间: 0 ms | 内存: 10.2 MB

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int l = matrix.size();
        for(int i=0; i<l;i++){
            for(int j=i+1;j<l;j++){
                int temp=matrix[i][j];
                matrix[i][j]=matrix[j][i];
                matrix[j][i]=temp;
            }
        }

        for(int i=0;i<l;i++){
            for(int j=0;j<l/2;j++){
                int temp=matrix[i][j];
                matrix[i][j]=matrix[i][l-1-j];
                matrix[i][l-1-j]=temp;
            }
        }
    }
};