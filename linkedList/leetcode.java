public class leetcode {
    public class ListNode {
        int val;
        ListNode next;

        ListNode(int val) {
            this.val = val;
        }
    }

    // Leetcode 876: getMid
    public ListNode getMidNode(ListNode node) {
        if (node == null || node.next == null)
            return node;
        ListNode slow = node;
        ListNode fast = node;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    // Leetcode 206 : reverseOfLL
    public ListNode reverseList(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode prev = null;
        ListNode curr = head;
        while (curr != null) {
            ListNode forw = curr.next;

            curr.next = prev;
            prev = curr;
            curr = forw;
        }

        return prev;
    }

    // Class Question: reverse Data.
    public void reverseListData(ListNode head) {
        if (head == null || head.next == null)
            return;

        ListNode curr = head;
        ListNode midNode = getMidNode(head);

        ListNode nhead = midNode.next;
        midNode.next = null;

        nhead = reverseList(nhead);
        ListNode curr1 = nhead;

        while (curr != null && curr1 != null) {
            int temp = curr.val;
            curr.val = curr1.val;
            curr1.val = temp;

            curr = curr.next;
            curr1 = curr1.next;
        }

        nhead = reverseList(nhead);
        midNode.next = nhead;
    }

    public ListNode getMidNode_02(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode slow = head;
        ListNode fast = head;
        while (fast != null && fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    // Leetcode 234: palindrome
    public boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null)
            return true;

        ListNode curr = head;
        ListNode midNode = getMidNode_02(curr);

        ListNode nhead = midNode.next;
        midNode.next = null;

        nhead = reverseList(nhead);
        ListNode curr1 = nhead;
        while (curr != null && curr1 != null) {
            if (curr.val != curr1.val)
                return false;

            curr = curr.next;
            curr1 = curr1.next;
        }
        nhead = reverseList(nhead);
        midNode.next = nhead;

        return true;
    }

    // Leetcode 19: remove Nth node from End
    public ListNode removeNthFromEnd(ListNode head, int n) {
        if (head == null || n == 0)
            return head;

        if (n == 1 && head.next == null)
            return null;

        ListNode slow = head, fast = head;
        while (n-- > 0)
            fast = fast.next;

        if (fast == null)
            return slow.next;

        while (fast.next != null) {
            fast = fast.next;
            slow = slow.next;
        }

        ListNode forw = slow.next;
        slow.next = slow.next.next;
        forw.next = null;

        return head;
    }

    // leetcode 143: reorder list
    public void reorderList(ListNode head) {
        if (head == null || head.next == null)
            return;

        ListNode mid = getMidNode_02(head);
        ListNode nhead = mid.next;
        mid.next = null;

        nhead = reverseList(nhead);

        ListNode curr1 = head;
        ListNode curr2 = nhead;

        ListNode forw1 = null;
        ListNode forw2 = null;

        while (curr1 != null && curr2 != null) {
            forw1 = curr1.next;
            forw2 = curr2.next;

            curr1.next = curr2;
            curr2.next = forw1;

            curr1 = forw1;
            curr2 = forw2;
        }
    }

    // Leetcode 21: merge Two LL.
    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if (l1 == null || l2 == null)
            return l1 == null ? l2 : l1;

        ListNode head = new ListNode(-1);
        ListNode prev = head;

        ListNode curr1 = l1;
        ListNode curr2 = l2;

        while (curr1 != null && curr2 != null) {
            if (curr1.val <= curr2.val) {
                prev.next = curr1;
                prev = curr1;
                curr1 = curr1.next;
            } else {
                prev.next = curr2;
                prev = curr2;
                curr2 = curr2.next;
            }
        }

        if (curr1 != null) {
            prev.next = curr1;
        }

        if (curr2 != null) {
            prev.next = curr2;
        }

        return head.next;
    }

    // Leetcode 328:
    public ListNode oddEven(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode odd = head;
        ListNode even = head.next;
        ListNode evenHead = even;

        while (even != null && even.next != null) {
            odd.next = even.next;
            odd = odd.next;
            even.next = odd.next;
            even = even.next;
        }
        odd.next = evenHead;
        return head;
    }

    // leetcode 141:
    public boolean hasCycle(ListNode head) {
        if (head == null || head.next == null)
            return false;

        ListNode slow = head, fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast)
                return true;
        }
        return false;
    }

    // leetcode 142.
    public ListNode detectCycle(ListNode head) {
        if (head == null || head.next == null)
            return null;

        ListNode slow = head;
        ListNode fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast)
                break;
        }

        if (slow != head)
            return head;

        slow = head;
        while (slow != fast) {
            slow = slow.next;
            fast = fast.next;
        }
        return slow;
    }

    // leetcode 160.
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if (headA == null || headB == null)
            return null;

        if (headA.next == null && headB.next == null) {
            if (headA.val == headB.val)
                return headA;
            else
                return null;
        }

        ListNode curr = headA;
        while (curr.next != null)
            curr = curr.next;

        curr.next = headA;
        ListNode rv = detectCycle(headB);
        curr.next = null;

        return rv;
    }

    // leetcode 148. sort list in NlogN
    public ListNode sortList(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode mid = getMidNode_02(head);
        ListNode nhead = mid.next;
        mid.next = null;

        return mergeTwoLists(sortList(head), sortList(nhead));
    }

    // leetcode 23. merger k sorted lists
    public ListNode mergerKLists(ListNode[] lists, int si, int ei) {
        if (si > ei)
            return null;
        if (si == ei)
            return lists[si];
        if (si + 1 == ei)
            return mergeTwoLists(lists[si], lists[si + 1]);
        int mid = (si + ei) / 2;
        return mergeTwoLists(mergerKLists(lists, si, mid), mergerKLists(lists, mid + 1, ei));
    }

    public ListNode mergeKLists(ListNode[] lists) {
        if (lists.length == 0) {
            return null;
        }
        int si = 0, ei = lists.length - 1;
        return mergerKLists(lists, si, ei);
    }

    // leetcode 92. reverse linked list 2
    ListNode temp_head = null;
    ListNode temp_tail = null;

    public ListNode reverseBetween(ListNode head, int m, int n) {
        if (head.next == null || m == n)
            return head;

        int idx = 1;
        ListNode curr = head;
        ListNode prev = null;
        ListNode nhead = head;

        while (curr != null) {
            while (idx >= m && idx <= n) {
                ListNode forw = curr.next;
                curr.next = null;

                if (temp_head == null) {
                    temp_head = curr;
                    temp_tail = curr;
                } else {
                    curr.next = temp_head;
                    temp_head = curr;
                }

                curr = forw;
                idx++;
            }

            if (temp_tail != null) {
                temp_tail.next = curr;
                if (prev != null)
                    prev.next = temp_head;
                else
                    nhead = temp_head;
                break;
            }

            prev = curr;
            curr = curr.next;
            idx++;
        }
        return nhead;
    }

    // leetcode 25. reverse nodes in K groups

    ListNode original_head = null;
    ListNode original_tail = null;

    ListNode temp_head_ = null;
    ListNode temp_tail_ = null;

    public int len(ListNode root) {
        int l = 0;
        while (root != null) {
            l++;
            root = root.next;
        }
        return l;
    }

    public ListNode reverseKGroup(ListNode head, int k) {
        if (head == null || head.next == null || k == 0 || k == 1)
            return head;

        int len = len(head);
        if (len < k)
            return head;

        ListNode curr = head;
        while (curr != null) {
            int tk = k; // temp k
            while (tk-- > 0) {
                ListNode forw = curr.next;
                curr.next = null;

                if (temp_head_ == null) {
                    temp_head_ = curr;
                    temp_tail_ = curr;
                } else {
                    curr.next = temp_head_;
                    temp_head_ = curr;
                }
                curr = forw;
            }

            len -= k;

            if (original_tail == null) {
                original_head = temp_head_;
                original_tail = temp_tail_;
            } else {
                original_tail.next = temp_head_;
                original_tail = temp_tail_;
            }

            temp_head_ = null;
            temp_tail_ = null;

            if (len < k) {
                original_tail.next = curr;
                curr = null;
            }
        }
        return original_head;
    }
}