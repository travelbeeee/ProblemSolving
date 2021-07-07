import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> ans = new ArrayList<>();
        int N = nums.length;
        Arrays.sort(nums);

        for (int i = 0; i < N - 2; i++){
            int left = i + 1, right = N - 1;
            while(left < right){
                System.out.println(i + " " + left + " " + right);
                int sum = nums[i] + nums[left] + nums[right];
                if(sum == 0){
                    if (!ans.contains(new ArrayList<>(Arrays.asList(nums[i], nums[left], nums[right])))) {
                        ans.add(new ArrayList<>(Arrays.asList(nums[i], nums[left], nums[right])));
                    }
                    left++;
                    right--;
                }
                else if (sum < 0){
                    left++;
                }
                else{
                    right--;
                }
            }
        }
        return ans;
    }
}
