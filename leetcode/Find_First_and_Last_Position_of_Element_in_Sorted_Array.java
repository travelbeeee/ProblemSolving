class Solution {
    public int[] searchRange(int[] nums, int target) {
        int leftInd = lowerBound(nums, target);
        int rightInd = upperBound(nums, target);
        if(leftInd > rightInd)
            return new int[]{-1, -1};
        return new int[]{leftInd, rightInd};
    }

    private int upperBound(int[] nums, int target) {
        int left = 0, right= nums.length - 1;
        while(left <= right){
            int mid = (left + right) / 2;
            if(nums[mid] <= target){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
        }
        return right;
    }

    private int lowerBound(int[] nums, int target) {
        int left = 0, right= nums.length - 1;
        while(left <= right){
            int mid = (left + right) / 2;
            if(nums[mid] < target){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
        }
        return left;
    }
}
