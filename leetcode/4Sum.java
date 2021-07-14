/*
 * Sorting 후, 2개의 기준 점을 잡고, 나머지 부분에 대해서 2 Pointer Search를 진행한다.
 */
import java.util.*;

class Solution {
    public List<List<Integer>> fourSum(int[] nums, int target) {
        Arrays.sort(nums);
        Map<List<Integer>, Boolean> m = new HashMap<>();
        for (int i = 0; i < nums.length; i++){
            for(int j = i + 1; j < nums.length; j++){
                int left = j + 1, right = nums.length;
                while(left < right){
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if(sum < target){
                        left++;
                    }
                    else if (sum > target){
                        right--;
                    }
                    else{
                        m.put(Arrays.asList(nums[i], nums[j], nums[left], nums[right]), true);
                        left++;
                        right--;
                    }
                }
            }
        }
        List<List<Integer>> ans = new ArrayList<>();
        ans.addAll(m.keySet());
        return ans;
    }

}
