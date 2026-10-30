// 提交编号: 757781878
// 提交时间: 2026-10-30 16:13:04
// 判题结果: Compile Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(k==1){
            return head;
        }
        int times=0;
        ListNode* p=head;
        ListNode* left,right;
        ListNode* next_seg=head;
        int first=0;
        while (p){
            times++;
            if(times==k){
                if(!first){
                    head=p;
                }
                first++;
                times=0;
                next_seg=p->next;
                p->next=left;
                for(int i=0;i<k;i++){
                    ListNode* p1=p,p2=p->next,p3=p2->next;
                    p2->next=p1;
                    p1=p2;
                    p2=p3;
                    p3=p3->next;
                }
                p=next_seg;
            }
            p=p->next;
        }
        return head;
    }
};