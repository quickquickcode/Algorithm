// 提交编号: 757321265
// 提交时间: 2026-10-27 22:55:39
// 判题结果: Accepted
// 运行时间: 47 ms (击败 5.05%) | 内存: 21.8 MB (击败 5.11%)

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        vector<int> list_i={};
        vector<int> list_j={};

        for(int i=0;i<matrix.size();i++){
            for(int j=0;j<matrix[0].size();j++){
                if(matrix[i][j] == 0){
                    list_i.push_back(i);
                    list_j.push_back(j);
                }
            }   
        }
        for(int i=0;i<list_i.size();i++){
            for(int j=0;j<matrix[0].size();j++){
                matrix[list_i[i]][j] = 0;
            }   
        }

        for(int i=0;i<matrix.size();i++){
            for(int j=0;j<list_j.size();j++){
                matrix[i][list_j[j]] = 0;
            }   
        }
    }
};