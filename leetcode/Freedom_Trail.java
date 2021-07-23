class Solution {
    int dp[][] = new int[100][101];

    public int findRotateSteps(String ring, String key) {
        for (int i = 0; i< ring.length(); i++)
            for(int j = 0; j < key.length() + 1; j++)
                dp[i][j] = Integer.MAX_VALUE;

        DFS(0, 0, 0, ring, key);

        int ans = Integer.MAX_VALUE;
        for (int i = 0; i < ring.length(); i++) {
            ans = Math.min(ans, dp[i][key.length()]);
        }
        return ans;
    }

    private void DFS(int ringInd, int keyInd, int step, String ring, String key) {
        if(keyInd == key.length())
            return;
        if(dp[ringInd][keyInd] < step)
            return;

        char goal = key.charAt(keyInd);
        int leftInd = ringInd, leftStep = 0;
        while(ring.charAt(leftInd) != goal){
            leftStep++;
            leftInd--;
            if(leftInd == -1) {
                leftInd = ring.length() - 1;
            }
        }
        if (step + leftStep + 1 < dp[leftInd][keyInd + 1]) {
            dp[leftInd][keyInd + 1] = step + leftStep + 1;
            DFS(leftInd, keyInd + 1, step + leftStep + 1, ring, key);
        }
        int rightInd = ringInd, rightStep = 0;
        while(ring.charAt(rightInd) != goal){
            rightStep++;
            rightInd++;
            if(rightInd == ring.length()) {
                rightInd = 0;
            }
        }
        if (step + rightStep + 1 < dp[rightInd][keyInd + 1]) {
            dp[rightInd][keyInd + 1] = step + rightStep + 1;
            DFS(rightInd, keyInd + 1, step + rightStep + 1, ring, key);
        }
    }

}
