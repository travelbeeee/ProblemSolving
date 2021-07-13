/**
 * 1) s[i]에서 시작해서 다른 알파벳이 나올때까지 탐색을 진행한다.
 * --> s[i] ~ s[i + sameAlpSize - 1]까지는 다 같은 알파벳! (팰린드롬)
 * 2) 1)에서 찾은 같은 알파벳으로 이루어져있는 팰린드롬의 양 옆을 탐색해서 추가로 팰린드롬 탐색을 진행한다.
 * 3) s[i] ~ s[i + sameAlpSize - 1]까지는 다 같은 알파벳이므로 다음 탐색을 i  + sameAlpSize 부터 진행하면 된다.
 *  그보다 작은 index 값들은 이미 s[i] 에서 탐색했을 때 최대를 찾은 경우가 된다.
 */
class Solution {
    public String longestPalindrome(String s) {
        StringBuilder ans = new StringBuilder();
        int ind = 0;
        while (ind < s.length()) {
            int sameAlpSize = 0;
            for (int j = ind; j < s.length(); j++){
                if(s.charAt(ind) != s.charAt(j)) break;
                sameAlpSize++;
            }
            // ind부터 ind + sameAlpSize - 1까지 같은 알파벳으로 Palindrome
            int size = sameAlpSize, j = 1;
            while(0 <= ind - j && ind + sameAlpSize - 1 + j < s.length()
                    && s.charAt(ind - j) == s.charAt(ind + sameAlpSize - 1 + j)){
                size += 2;
                j++;
            }
            if(ans.length() < size){
                ans = new StringBuilder(s.substring(ind - j + 1, ind + sameAlpSize - 1 + j));
            }
            ind += sameAlpSize;
        }
        return ans.toString();
    }
}
