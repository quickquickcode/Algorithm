// 提交编号: 757214383
// 提交时间: 2026-10-27 15:17:44
// 判题结果: Compile Error
// 运行时间: N/A | 内存: N/A

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
    }
};