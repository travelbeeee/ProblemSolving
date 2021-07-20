/*
*  DP + BFS
*/
import java.util.*;

class Solution {
    public int minPathSum(int[][] grid) {
        int n = grid.length;
        int m = grid[0].length;

        int dp[][] = new int[n][m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                dp[i][j] = Integer.MAX_VALUE;
        dp[0][0] = grid[0][0];

        Queue<Pointer> q = new LinkedList<>();
        q.add(new Pointer(0, 0, dp[0][0]));
        int dx[] = {1, 0};
        int dy[] = {0, 1};
        
        while (!q.isEmpty()) {
            Pointer cur = q.poll();
            if(cur.x == n - 1 && cur.y == m - 1) continue;
            if(dp[cur.x][cur.y] < cur.sum) continue;
            
            for (int dir = 0; dir < 2; dir++){
                int nextX = cur.x + dx[dir], nextY = cur.y + dy[dir];
                if(!(0 <= nextX && nextX < n && 0 <= nextY && nextY < m)) continue;
                if (cur.sum + grid[nextX][nextY] < dp[nextX][nextY]) {
                    q.add(new Pointer(nextX, nextY, cur.sum + grid[nextX][nextY]));
                    dp[nextX][nextY] = cur.sum + grid[nextX][nextY];
                }
            }
        }
        return dp[n - 1][m - 1];
    }
    
    private class Pointer {
        int x, y, sum;
        public Pointer(int x, int y, int sum) {
            this.x = x;
            this.y = y;
            this.sum = sum;
        }
    }
}
