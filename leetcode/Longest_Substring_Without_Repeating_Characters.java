/**
 * Sliding Window
 *
 * left ~ (right - 1) 까지 우리가 원하는 substring인지 체크하며 범위를 늘려간다.
 * right가 이미 가지고 있는 문자라면, 이미 가지고 있는 문자가 없는 범위까지 left를 끌어올린다.
 */
class Solution {
    public int lengthOfLongestSubstring(String s) {
        if(s.isEmpty()) return 0;

        int maxLen = 0;
        Boolean[] visited =new Boolean[128]; // 아스키코드 32번 space ~ 127번까지
        for (int i = 0; i < 128; i++) visited[i] = false;

        int left = 0, right = 0, N = s.length();
        while (right < N) {
            if(!visited[s.charAt(right)]){
                visited[s.charAt(right)] = true;
                maxLen = Math.max(maxLen, right - left + 1);
                right++;
            }
            else{
                while(visited[s.charAt(right)]){
                    visited[s.charAt(left)] = false;
                    left++;
                }
            }
        }
        return maxLen;
    }

    private int changeToNum(char c){
        return c;
    }
}
