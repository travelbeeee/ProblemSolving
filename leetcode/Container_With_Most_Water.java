/**
 * Two Pointer
 *
 * left ~ right 까지의 Area는 다음과 같다.
 * 가로 * 세로 = (right - left) * Math.min(height[left], height[right]);
 *
 * 가로가 가장 긴 상태에서 시작해서, 높이가 낮은 쪽을 하나씩 바꿔가면서 진행하자.
 */
class Solution {
    public int maxArea(int[] height) {
        int maxArea = 0;
        int left = 0, right = height.length - 1;
        while(left < right){
            int curArea = Math.min(height[left], height[right]) * (right - left);
            if(height[left] < height[right]) left++;
            else right--;
            maxArea = Math.max(maxArea, curArea);
        }
        return maxArea;
    }
}
