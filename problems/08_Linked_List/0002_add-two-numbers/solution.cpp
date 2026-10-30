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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* p=new ListNode(0,nullptr);
        ListNode* result=new ListNode(0,p);
        int in=0;
        while(l1 || l2 ){
            if(l1 && l2){
                ListNode* t=new ListNode((l1->val+l2->val+in)%10,nullptr);
                in=(l1->val+l2->val+in)/10;
                l1=l1->next;l2=l2->next;
                p->next=t;
                p=p->next;
            }
            else if(l1){
                ListNode* t=new ListNode((l1->val+in)%10,nullptr);
                in=(l1->val+in)/10;
                l1=l1->next;
                p->next=t;
                p=p->next;
            }
            else if(l2){
                ListNode* t=new ListNode((l2->val+in)%10,nullptr);
                in=(l2->val+in)/10;
                l2=l2->next;
                p->next=t;
                p=p->next;
            }
        }
        if(in){
            ListNode* t=new ListNode((in)%10,nullptr);
            p->next=t;
            p=p->next;
        }
        return result->next->next;
    }
};