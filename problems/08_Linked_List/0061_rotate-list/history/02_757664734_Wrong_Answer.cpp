// 提交编号: 757664734
// 提交时间: 2026-10-29 20:21:46
// 判题结果: Wrong Answer
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
    ListNode* rotateRight(ListNode* head, int k) {
        int n=0;
        ListNode* p=head; 
        if(p==nullptr){
            return p;
        }
        while(p->next){
            p=p->next;
            n++;
        }
        k=k%(n+1);

        ListNode* left=head; 
        ListNode* temp = left->next; 
        for(int i=0;i<k;i++){
            left->next=nullptr;
            p->next=left;
            left=temp;
            temp = left->next;
            p=p->next;
        }
        return left;
    }
};