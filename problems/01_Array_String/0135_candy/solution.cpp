#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n <= 1) return n;

        // 初始每个孩子至少分得 1 颗糖果
        vector<int> candies(n, 1);

        // 1. 从左向右遍历：落实“左规则”
        // 只要当前孩子评分高于左边邻居，就比左边邻居多拿 1 颗
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // 2. 从右向左遍历：落实“右规则”
        // 只要当前孩子评分高于右边邻居，且原有糖果数不占优，更新为 candies[i + 1] + 1
        // 注意：必须取 max，同时兼容左规则与右规则
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }

        // 3. 统计总糖果数
        return accumulate(candies.begin(), candies.end(), 0);
    }
};
