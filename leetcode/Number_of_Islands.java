import java.util.LinkedList;
import java.util.Queue;

class Solution {
    public int numIslands(char[][] grid) {
        int m = grid.length;
        int n= grid[0].length;

        int nIsland = 0;
        boolean visited[][] = new boolean[m][n];
        for (int row = 0; row < m; row++){
            for(int col = 0; col < n; col++){
                if(!visited[row][col] && grid[row][col] == '1'){
                    BFS(row, col, m, n, visited, grid);
                    nIsland++;
                }
            }
        }
        return nIsland;
    }

    private void BFS(int row, int col, int m, int n, boolean[][] visited, char[][] grid) {
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, -1, 0, 1};
        Queue<Point> q = new LinkedList<>();
        q.add(new Point(row, col));
        visited[row][col] = true;
        while (!q.isEmpty()) {
            Point cur = q.poll();
            for (int dir = 0; dir < 4; dir++){
                int nextX = cur.x + dx[dir];
                int nextY = cur.y + dy[dir];
                if(!checkCanGo(nextX, nextY, m, n, visited, grid)) continue;
                visited[nextX][nextY] = true;
                q.add(new Point(nextX, nextY));
            }
        }
    }

    private boolean checkCanGo(int nextX, int nextY, int m, int n, boolean[][] visited, char[][] grid) {
        if(!(0 <= nextX && nextX < m && 0 <= nextY && nextY < n)) return false;
        if(visited[nextX][nextY]) return false;
        if(grid[nextX][nextY] == '0') return false;
        return true;
    }

    private class Point {
        int x, y;
        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}
