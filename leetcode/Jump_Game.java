class Solution {
    public boolean canJump(int[] nums) {
        int N = nums.length, endPoint = N - 1; // endPoint 만 도착하면 끝까지 갈 수 있음.
        for (int i = N - 1; i >= 0; i--){
            if(i + nums[i] >= endPoint){ // i에서 현재 endPoint까지 갈 수 있으면 endPoint 갱신
                endPoint = i;
            }
        }
        return endPoint == 0;
    }
}
