import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode res = new ListNode();
        ListNode cur = res;
        int up = 0, digit = 0;
        while(l1 != null || l2 != null){
            if(l1 != null && l2 != null){
                digit = l1.val + l2.val + up;
                l1 = l1.next;
                l2 = l2.next;
            }
            else if (l1 != null){
                digit = l1.val + up;
                l1 = l1.next;
            }
            else if (l2 != null){
                digit = l2.val + up;
                l2 = l2.next;
            }

            if(digit >= 10){
                up++;
                digit -= 10;
            }
            else {
                up = 0;
            }
            cur.val = digit;
            ListNode next = new ListNode();
            cur.next = next;
            cur = next;
        }
        return res;
    }

    private ListNode getListNodeByInteger(BigInteger resInteger) {
        ListNode listNode = new ListNode();
        BigInteger[] bigIntegers = resInteger.divideAndRemainder("10");

    }

    private StringBuffer getNumberByString(ListNode listNode) {
        StringBuffer res = new StringBuffer();
        while(listNode != null){
            res.append(listNode.val);
            listNode = listNode.next;
        }
        return res;
    }

    private class ListNode {
        int val;
        ListNode next;
        ListNode() {}
        ListNode(int val) {this.val = val;}
        ListNode(int val, ListNode next) {this.val = val; this.next =next;}
    }
}
