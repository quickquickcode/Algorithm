// 提交编号: 757214526
// 提交时间: 2026-10-27 15:18:12
// 判题结果: Accepted
// 运行时间: 0 ms | 内存: 11.5 MB

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0, fast = 0;
        while (fast < nums.size()){
            if (nums[fast] != val){
                nums[slow]=nums[fast];
                slow++;
            }
            fast++;
        }
        return slow;
    }
};