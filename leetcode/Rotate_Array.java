import java.util.Deque;
import java.util.LinkedList;

class Solution {
    public void rotate(int[] nums, int k) {
        int N = nums.length;

        Deque<Integer> q = new LinkedList<>();
        for (int i = 0; i < N; i++) {
            q.addLast(nums[i]);
        }
        for (int i = 0; i < k; i++){
            q.addFirst(q.pollLast());
        }
        for (int i = 0; i < N; i++){
            nums[i] = q.pollFirst();
        }
    }
}
