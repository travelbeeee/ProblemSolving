/*
    Dynamic Programming
    
    dp[l][0] := l길이에 끝이 'a'로 끝나는 str의 수
    dp[l][1] := l길이에 끝이 'e'로 끝나는 str의 수
    dp[l][2] := l길이에 끝이 'i'로 끝나는 str의 수
    dp[l][3] := l길이에 끝이 'o'로 끝나는 str의 수
    dp[l][4] := l길이에 끝이 'u'로 끝나는 str의 수
 */
class Solution {
    static final int m = 1000000007;
    static int[][] dp = new int[20001][5]; // a e i o u

    public int countVowelPermutation(int n){
        setDp(n);

        int res = 0;
        for (int j = 0; j < 5; j++)
            res = (res + dp[n][j]) % m;
        return res;
    }

    void setDp(int n){
        for (int i = 1; i <= n; i++)
            for(int j = 0; j < 5; j++)
                dp[i][j] = 0;

        dp[1][0] = dp[1][1] = dp[1][2] =dp[1][3] = dp[1][4] = 1;
        for (int i = 2; i <= n; i++){
            dp[i][0] += ((dp[i - 1][1] + dp[i - 1][2]) % m + dp[i - 1][4]) % m;
            dp[i][1] += (dp[i - 1][0] + dp[i - 1][2]) % m;
            dp[i][2] += (dp[i - 1][1] + dp[i - 1][3]) % m;
            dp[i][3] += dp[i - 1][2];
            dp[i][4] += (dp[i - 1][2] + dp[i - 1][3]) % m; // 'a' followed by 'e'
        }
    }
}
