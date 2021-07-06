/*
* Sorting 후, 맨 앞부터 기준점 하나와 투포인터를 이용한다.
*/
import java.util.Arrays;

class Solution {
    public int threeSumClosest(int[] nums, int target) {
        int diff = Integer.MAX_VALUE, N = nums.length;

        Arrays.sort(nums);
        
        for (int i = 0; i < N; i++){
            int left = i + 1, right = N - 1;
            while(left < right){
                int sum = nums[i] + nums[left] + nums[right];
                if(Math.abs(target - sum) < Math.abs(diff)){
                    diff = target - sum;
                }
                if(sum < target)
                    left++;
                else
                    right--;
            }
            if(diff == 0) break;
        }
        return target - diff;
    }
}
