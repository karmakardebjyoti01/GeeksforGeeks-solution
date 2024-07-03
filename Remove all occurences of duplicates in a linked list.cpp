class Solution {
  public:
    Node* removeAllDuplicates(struct Node* head) {
        // code here
        Node* res = new Node(-1);
        res->next = head;
        
        Node* preptr = res;
        
        Node* curr = head;
        while(curr!=nullptr)
        {
            while(curr->next!=nullptr && preptr->next->data == curr->next->data)
            {
                curr = curr->next;
            }
            
            if(preptr->next==curr)
            {
                preptr=preptr->next;
            }
            else
                preptr->next = curr->next;
                
                curr = curr->next;
        }
        
        return res->next;
    }
};
