#include <iostream>
#include <vector>
using namespace std;
class leetcode
{
public:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    // Leetcode 876: getMid
    ListNode *getMidNode(ListNode *node)
    {
        if (node == nullptr || node->next == nullptr)
            return node;
        ListNode *slow = node;
        ListNode *fast = node;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // Leetcode 206 : reverseOfLL
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *prev = nullptr;
        ListNode *curr = head;
        while (curr != nullptr)
        {
            ListNode *forw = curr->next;

            curr->next = prev;
            prev = curr;
            curr = forw;
        }

        return prev;
    }

    // Class Question: reverse Data->
    void reverseListData(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode *curr = head;
        ListNode *midNode = getMidNode(head);

        ListNode *nhead = midNode->next;
        midNode->next = nullptr;

        nhead = reverseList(nhead);
        ListNode *curr1 = nhead;

        while (curr != nullptr && curr1 != nullptr)
        {
            int temp = curr->val;
            curr->val = curr1->val;
            curr1->val = temp;

            curr = curr->next;
            curr1 = curr1->next;
        }

        nhead = reverseList(nhead);
        midNode->next = nhead;
    }

    ListNode *getMidNode_02(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != nullptr && fast->next != nullptr && fast->next->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // Leetcode 234: palindrome
    bool isPalindrome(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return true;

        ListNode *curr = head;
        ListNode *midNode = getMidNode_02(curr);

        ListNode *nhead = midNode->next;
        midNode->next = nullptr;

        nhead = reverseList(nhead);
        ListNode *curr1 = nhead;
        while (curr != nullptr && curr1 != nullptr)
        {
            if (curr->val != curr1->val)
                return false;

            curr = curr->next;
            curr1 = curr1->next;
        }
        nhead = reverseList(nhead);
        midNode->next = nhead;

        return true;
    }

    // Leetcode 19: remove Nth node from End
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        if (head == nullptr || n == 0)
            return head;

        if (n == 1 && head->next == nullptr)
            return nullptr;

        ListNode *slow = head, *fast = head;
        while (n-- > 0)
            fast = fast->next;

        if (fast == nullptr)
            return slow->next;

        while (fast->next != nullptr)
        {
            fast = fast->next;
            slow = slow->next;
        }

        ListNode *forw = slow->next;
        slow->next = slow->next->next;
        forw->next = nullptr;

        return head;
    }

    // leetcode 143: reorder list
    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode *mid = getMidNode_02(head);
        ListNode *nhead = mid->next;
        mid->next = nullptr;

        nhead = reverseList(nhead);

        ListNode *curr1 = head;
        ListNode *curr2 = nhead;

        ListNode *forw1 = nullptr;
        ListNode *forw2 = nullptr;

        while (curr1 != nullptr && curr2 != nullptr)
        {
            forw1 = curr1->next;
            forw2 = curr2->next;

            curr1->next = curr2;
            curr2->next = forw1;

            curr1 = forw1;
            curr2 = forw2;
        }
    }

    // Leetcode 21: merge Two LL->
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr || l2 == nullptr)
            return l1 == nullptr ? l2 : l1;

        ListNode *head = new ListNode(-1);
        ListNode *prev = head;

        ListNode *curr1 = l1;
        ListNode *curr2 = l2;

        while (curr1 != nullptr && curr2 != nullptr)
        {
            if (curr1->val <= curr2->val)
            {
                prev->next = curr1;
                prev = curr1;
                curr1 = curr1->next;
            }
            else
            {
                prev->next = curr2;
                prev = curr2;
                curr2 = curr2->next;
            }
        }

        if (curr1 != nullptr)
        {
            prev->next = curr1;
        }

        if (curr2 != nullptr)
        {
            prev->next = curr2;
        }

        return head->next;
    }

    // Leetcode 328:
    ListNode *oddEven(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *odd = head;
        ListNode *even = head->next;
        ListNode *evenHead = even;

        while (even != nullptr && even->next != nullptr)
        {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
        return head;
    }

    // leetcode 141:
    bool hasCycle(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return false;

        ListNode *slow = head, *fast = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
    }

    // leetcode 142->
    ListNode *detectCycle(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return nullptr;

        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                break;
        }

        if (slow != head)
            return head;

        slow = head;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }

    // leetcode 160->
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        if (headA == nullptr || headB == nullptr)
            return nullptr;

        if (headA->next == nullptr && headB->next == nullptr)
        {
            if (headA->val == headB->val)
                return headA;
            else
                return nullptr;
        }

        ListNode *curr = headA;
        while (curr->next != nullptr)
            curr = curr->next;

        curr->next = headA;
        ListNode *rv = detectCycle(headB);
        curr->next = nullptr;

        return rv;
    }

    // leetcode 148-> sort list in NlogN
    ListNode *sortList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *mid = getMidNode_02(head);
        ListNode *nhead = mid->next;
        mid->next = nullptr;

        return mergeTwoLists(sortList(head), sortList(nhead));
    }

    // leetcode 23. merger k sorted lists
    ListNode *mergerKLists(vector<ListNode *> &lists, int si, int ei)
    {
        if (si > ei)
            return nullptr;
        if (si == ei)
            return lists[si];
        if (si + 1 == ei)
            return mergeTwoLists(lists[si], lists[si + 1]);
        int mid = (si + ei) / 2;
        return mergeTwoLists(mergerKLists(lists, si, mid), mergerKLists(lists, mid + 1, ei));
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (lists.size() == 0)
        {
            return nullptr;
        }
        int si = 0, ei = lists.size() - 1;
        return mergerKLists(lists, si, ei);
    }

    // leetcode 92. reverse linked list 2
    ListNode *temp_head = nullptr;
    ListNode *temp_tail = nullptr;
    ListNode *reverseBetween(ListNode *head, int m, int n)
    {
        std::ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        if (head->next == nullptr || m == n)
            return head;
        int idx = 1;
        ListNode *curr = head;
        ListNode *prev = nullptr;
        ListNode *nhead = head;
        while (curr != nullptr)
        {
            while (idx >= m && idx <= n)
            {
                ListNode *forw = curr->next;
                curr->next = nullptr;

                if (temp_head == nullptr)
                {
                    temp_head = curr;
                    temp_tail = curr;
                }
                else
                {
                    curr->next = temp_head;
                    temp_head = curr;
                }

                curr = forw;
                idx++;
            }

            if (temp_tail != nullptr)
            {
                temp_tail->next = curr;
                if (prev != nullptr)
                    prev->next = temp_head;
                else
                    nhead = temp_head;
                break;
            }

            prev = curr;
            curr = curr->next;
            idx++;
        }
        return nhead;
    }

    // leetcode 25. Reverse Nodes in k-Group
    ListNode *original_head = nullptr;
    ListNode *original_tail = nullptr;

    ListNode *temp_head_ = nullptr;
    ListNode *temp_tail_ = nullptr;
    int len_(ListNode *node)
    {
        int l = 0;
        while (node != nullptr)
        {
            l++;
            node = node->next;
        }
        return l;
    }

    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        if (head == nullptr || head->next == nullptr || k == 0 || k == 1)
            return head;

        int len = len_(head);
        if (len < k)
            return head;

        ListNode *curr = head;
        while (curr != nullptr)
        {
            int tk = k;
            while (tk-- > 0)
            {
                ListNode *forw = curr->next;
                curr->next = nullptr;

                if (temp_head_ == nullptr)
                {
                    temp_head_ = curr;
                    temp_tail_ = curr;
                }
                else
                {
                    curr->next = temp_head_;
                    temp_head_ = curr;
                }
                curr = forw;
            }

            len -= k;

            if (original_tail == nullptr)
            {
                original_head = temp_head_;
                original_tail = temp_tail_;
            }
            else
            {
                original_tail->next = temp_head_;
                original_tail = temp_tail_;
            }

            temp_head_ = nullptr;
            temp_tail_ = nullptr;

            if (len < k)
            {
                original_tail->next = curr;
                curr = nullptr;
            }
        }
        return original_head;
    }

    // another way to solve this question
    // but i will prefer the last one
    ListNode *reverseKGroup02(ListNode *head, int k)
    {
        std::ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        if (head == nullptr || head->next == nullptr)
            return head;

        int len = len_(head);

        if (len < k)
            return head;

        ListNode *nhead = nullptr;
        ListNode *ntail = head;

        while (head != nullptr)
        {
            ListNode *ttail = nullptr;
            ListNode *rev = nullptr;
            int temp = k;

            if (len >= k)
            {
                while (head != nullptr && temp != 0)
                {
                    if (ttail == nullptr)
                        ttail = head;

                    ListNode *forw = head->next;
                    head->next = rev;

                    rev = head;
                    head = forw;

                    temp--;
                }

                len -= k;

                if (nhead == nullptr)
                    nhead = rev;
                else
                {
                    ntail->next = rev;
                    ntail = ttail;
                }
            }
            else
            {
                ntail->next = head;
                break;
            }
        }
        return nhead;
    }

    // leetcode 61. rotate list

    /* I first used a ListNode p, and point it to the head, then move it to the end of the list,
    and at the same time get the length of the list. Then p.next = head; gives me a circle.
    At this time, by moving p for len-k times, it will be pointing to the node before the break point.
    Then all we need to do is record the next node as head, and break the circle with p.next = null. */

    ListNode *rotateRight(ListNode *head, int k)
    {
        if (head == nullptr || head->next == nullptr || k == 0)
            return head;
        ListNode *p = head;
        int len = 1;
        while (p->next != nullptr)
        {
            len++;
            p = p->next;
        }

        p->next = head;
        k %= len;
        for (int i = 0; i < len - k; i++)
            p = p->next;

        ListNode *nhead = p->next;
        p->next = nullptr;
        return nhead;
    }

    // leetcode 203. Remove Linked List Elements
    ListNode *removeElements(ListNode *head, int val)
    {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        ListNode *nhead = new ListNode(-1);
        nhead->next = head;

        ListNode *prev = nhead, *curr = head;
        while (curr != nullptr)
        {
            if (curr->val == val)
                prev->next = curr->next;
            else
                prev = prev->next;
            curr = curr->next;
        }
        return nhead->next;
    }

    // leetcode 83. Remove Duplicates from Sorted List
    ListNode *deleteDuplicates(ListNode *head)
    {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *curr = head->next;
        ListNode *prev = head;
        while (curr != nullptr)
        {
            if (curr->val == prev->val)
                prev->next = curr->next;
            else
                prev = prev->next;
            curr = curr->next;
        }
        return head;
    }

    // leetcode 1019. Next Greater Node In Linked List
    vector<int> nextLargerNodes(ListNode *head)
    {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        vector<int> res, stack;
        for (ListNode *curr = head; curr != nullptr; curr = curr->next)
        {
            while (stack.size() && res[stack.back()] < curr->val)
            {
                res[stack.back()] = curr->val;
                stack.pop_back();
            }
            stack.push_back(res.size());
            res.push_back(curr->val);
        }

        for (int i : stack)
            res[i] = 0;
        return res;
    }
};
