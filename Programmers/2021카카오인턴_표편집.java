/*
* Double Linked List
*/
import java.util.ArrayList;
import java.util.Stack;

class Solution {
    public String solution(int n, int k, String[] cmd) {
        ArrayList<Node> nodelist = new ArrayList<>();
        for (int i = 0; i < n; i++)
            nodelist.add(new Node(i));
        for (int i = 0; i < n - 1; i++)
            nodelist.get(i).next = nodelist.get(i + 1);
        for (int i = 1; i < n; i++)
            nodelist.get(i).prev = nodelist.get(i - 1);

        Node pointer = nodelist.get(k);
        Stack<Node> removedNode = new Stack<>();

        for (String op : cmd) {
            if(op.equals("C")){
                removedNode.push(pointer);
                if(pointer.prev == null){ // 삭제행이 맨 앞 행
                    pointer.next.prev = null;
                    pointer = pointer.next;
                }
                else if (pointer.next == null){ // 삭제행이 맨 뒷 행
                    pointer.prev.next = null;
                    pointer = pointer.prev;
                }
                else{
                    pointer.prev.next = pointer.next;
                    pointer.next.prev = pointer.prev;
                    pointer = pointer.next;
                }
            }
            else if (op.charAt(0) == 'D'){
                int moveCnt = Integer.parseInt(op.substring(2));
                while(moveCnt > 0){
                    pointer = pointer.next;
                    moveCnt--;
                }
            }
            else if (op.charAt(0) == 'U'){
                int moveCnt = Integer.parseInt(op.substring(2));
                while(moveCnt > 0){
                    pointer = pointer.prev;
                    moveCnt--;
                }
            }
            else{
                Node node = removedNode.pop();
                if(node.next != null) node.next.prev = node;
                if(node.prev != null) node.prev.next = node;
            }
        }
        Boolean removed[] = new Boolean[1000000];
        for (int i = 0; i < n; i++)
            removed[i] = false;
        while(!removedNode.isEmpty()){
            removed[removedNode.pop().value] = true;
        }
        StringBuilder answer = new StringBuilder();
        for (int i = 0; i < n; i++)
            if(removed[i]) answer.append('X');
            else answer.append('O');
        return answer.toString();
    }

    public class Node{
        int value;
        Node prev = null;
        Node next = null;

        public Node(int value) {
            this.value = value;
        }

        public void setPrev(Node prev) {
            this.prev = prev;
        }

        public void setNext(Node next) {
            this.next = next;
        }
    }
}
