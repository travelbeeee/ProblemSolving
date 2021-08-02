/**
 * nums 를 산의 높이라고 생각해보면 우리는 산의 정상 봉우리를 찾기만 하면 됨
 * --> 지금 보고 있는 곳보다 양쪽이 더 크면 왼쪽으로 가도 정상 봉우리가 있고,
 *     오른쪽으로 가도 정상 봉우리가 있을 것이다.
 */
class Solution {
    public int findPeakElement(int[] nums) {
        if(nums.length == 1){
            return nums[0];
        }
        int left = 0, right = nums.length - 1;
        while(left <= right){
            int mid = (left + right) / 2;
            if(mid == 0 && nums[mid] > nums[mid + 1])
                return mid;
            if(mid == nums.length - 1 && nums[mid - 1] < nums[mid])
                return mid;
            if(mid != 0 && mid != nums.length -1 &&
                    nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1])
                return mid;
            if(mid != 0 && nums[mid - 1] > nums[mid]){
                right = mid - 1;
            }
            else if (mid != nums.length -1 && nums[mid] < nums[mid + 1]){
                left = mid + 1;
            }
        }
        return nums[left];
    }
}
