// 48. 旋转图像 (Rotate Image)
// 核心解法：主对角线转置 + 垂直中线对称翻转
// 时间复杂度：O(N^2)，空间复杂度：O(1) 原地修改
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // 1. 沿主对角线 (i, j) 与 (j, i) 镜像翻转（矩阵转置）
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // 2. 沿垂直中线左右镜像翻转
        // 注意：第 j 列对应对称列是 n - 1 - j（严防数组越界 Off-by-one）
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                swap(matrix[i][j], matrix[i][n - 1 - j]);
            }
        }
    }
};
