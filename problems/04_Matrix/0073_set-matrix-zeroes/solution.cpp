// [73. Set Matrix Zeroes] 矩阵置零
// 力扣链接: https://leetcode.cn/problems/set-matrix-zeroes/

#include <vector>
#include <iostream>

using namespace std;

// ========================================================
// 解法一：当前通过解（坐标记录法 / 待进化）
// 时间复杂度: 最坏 O(M * N + |list_i| * N + M * |list_j|) -> 当全为0时退化为 O(M^2 * N + M * N^2)
// 空间复杂度: O(M * N) 使用了两个动态 vector 收集 0 坐标
// 实际测评: 47 ms (击败 5.05%) | 21.8 MB (击败 5.11%)
// ========================================================
class SolutionCurrent {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        vector<int> list_i = {};
        vector<int> list_j = {};

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 0) {
                    list_i.push_back(i);
                    list_j.push_back(j);
                }
            }   
        }
        for (int i = 0; i < list_i.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                matrix[list_i[i]][j] = 0;
            }   
        }

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < list_j.size(); j++) {
                matrix[i][list_j[j]] = 0;
            }   
        }
    }
};

// ========================================================
// 解法二：标杆进阶最优解（首行首列复用标记法 / 原地 O(1) 空间）
// 时间复杂度: O(M * N) 两次纯双层循环，零重复访问
// 空间复杂度: O(1) 仅用两个 bool 变量维护首行首列状态，其余标记借用 matrix[0][j] 与 matrix[i][0]
// 实际测评: 0 ms (击败 100%) | 17.5 MB (击败 85%+)
// ========================================================
class SolutionOptimal {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        bool first_row_zero = false;
        bool first_col_zero = false;

        // 1. 先检查首行是否本来就含有 0
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                first_row_zero = true;
                break;
            }
        }

        // 2. 检查首列是否本来就含有 0
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                first_col_zero = true;
                break;
            }
        }

        // 3. 用首行和首列当作天然的“黑名单哈希表”
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0; // 标记第 i 行要清零
                    matrix[0][j] = 0; // 标记第 j 列要清零
                }
            }
        }

        // 4. 根据首行首列的标记，将内部元素置零
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 5. 最后单独处理首行
        if (first_row_zero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }

        // 6. 最后单独处理首列
        if (first_col_zero) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

class Solution : public SolutionOptimal {};
