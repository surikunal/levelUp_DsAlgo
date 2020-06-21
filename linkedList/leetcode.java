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

    
}