// 提交编号: 757202807
// 提交时间: 2026-10-27 14:34:11
// 判题结果: Accepted
// 运行时间: 0 ms | 内存: 12.2 MB

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p=m-1,q=n-1;
        int x=m+n-1;
        while (q>=0){
            if(p>=0 && nums1[p] > nums2[q]){
                nums1[x]=nums1[p];
                x--;
                p--;
            }
            else{
                nums1[x]=nums2[q];
                x--;
                q--;
            }
        }
    }
};