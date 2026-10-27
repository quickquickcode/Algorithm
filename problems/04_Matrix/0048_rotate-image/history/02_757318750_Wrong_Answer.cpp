// 提交编号: 757318750
// 提交时间: 2026-10-27 22:42:40
// 判题结果: Wrong Answer
// 运行时间: N/A | 内存: N/A

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
                matrix[i][j]=matrix[i][l-j];
                matrix[i][l-j]=temp;
            }
        }
    }
};