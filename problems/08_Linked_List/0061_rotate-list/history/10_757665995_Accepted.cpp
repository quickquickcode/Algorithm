// 提交编号: 757665995
// 提交时间: 2026-10-29 20:27:40
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 16.1 MB (击败 60.06%)

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
        if(p==nullptr || p->next==nullptr){
            return p;
        }
        while(p->next){
            p=p->next;
            n++;
        }
        k=(n+1)-k%(n+1);

        ListNode* left=head; 
        ListNode* temp = left->next; 
        for(int i=0;i<k;i++){
            temp = left->next;
            p->next=left;
            p=p->next;
            p->next=nullptr;
            
            left=temp;
        }
        return left;
    }
};