import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> sets = new ArrayList<>();
        List<Integer> set = new ArrayList<>();
        backtracking(0, set, nums, sets);
        return sets;
    }

    private void backtracking(int ind, List<Integer> set,int[] nums, List<List<Integer>> res) {
        res.add(new ArrayList<>(set));

        for (int i = ind; i < nums.length; i++){
            set.add(nums[i]);
            backtracking(i + 1, set, nums, res);
            set.remove(set.size() - 1);
        }
    }
}
