struct ListNode{
    int val;
    ListNode* next;
    ListNode():val(0),next(nullptr){};
    ListNode(int x):val(x),next(nullptr){};
    ListNode(int x,ListNode* next):val(x),next(next){};
};

class solution{
public:
   ListNode* rotateRight(ListNode* head, int k) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = reverse(head);
        int size = 0;
        ListNode* cur = dummy->next;
        while (cur != nullptr) {
            ++size;
            cur = cur->next;
        }
        if (size <= 1) return head;
        k = k % size;
        // [DUMMY/PRE] >> [START] >> [NODE] >> [END] >> [NEXT] >> [NODE]
        ListNode* pre = dummy, * end = dummy;
        for (int i = 0; i < k; ++i) end = end->next;
        ListNode* start = pre->next, * next = end->next;
        // 防止 K 为 0 的情况发生
        if (start == next) return reverse(start);
        // [PRE] >> [START] >> [NODE] >> [END] || [NEXT] >> [NODE]
        end->next = nullptr;
        // [PRE] >> [END] >> [NODE] >> [START] || [NODE] >> [NEXT]
        pre->next = reverse(start);
        start->next = reverse(next);
        return dummy->next;
    }

    ListNode* reverse(ListNode* head) {
        ListNode* pre =  nullptr, * cur = head;
        while (cur != nullptr) {
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};