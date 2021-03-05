/*
  BFS DP
  
  dp[i][j][dir] := (i, j)에 dir방향으로 도로를 만들고 도착했을 때 최소 
*/
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 99999999;
const int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };

bool isInside(int x, int y, int N) {
    return (0 <= x && x < N && 0 <= y && y < N);
}

int solution(vector<vector<int>> board) {
    int N = board.size();
    int dp[25][25][2] = {};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dp[i][j][0] = dp[i][j][1] = INF;

    dp[0][0][0] = dp[0][0][1] = 0;
    queue<pair<pair<int, int>, pair<bool, int>>> q;
    if (board[0][1] == 0) {
        q.push({ {0, 1}, {false, 100} });
        dp[0][1][0] = 100; // (0,1) 에서 가로직선으로도착
    }
    if (board[1][0] == 0) {
        q.push({ {1, 0}, {1, 100} });
        dp[1][0][1] = 100;
    }
    while (!q.empty()) {
        pair<int, int> cur = q.front().first;
        bool curD = q.front().second.first;
        int curP = q.front().second.second;
        q.pop();

        if (cur.first == N - 1 && cur.second == N - 1) continue;
        
        // curD가 0이라면 가로직선 1이라면 세로직선
        for (int i = 0; i < 4; i++) { 
            int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
            if (!isInside(nextX, nextY, N)) continue;
            if (board[nextX][nextY]) continue;
            
            if (i < 2) { // 위아래이동
                int nextP = curP + 100 + 500 * !curD;
                if (nextP < dp[nextX][nextY][1]) {
                    dp[nextX][nextY][1] = nextP;
                    q.push({ {nextX, nextY}, {1, nextP} });
                }
            }
            else { // 양옆이동
                int nextP = curP + 100 + 500 * curD;
                if (nextP < dp[nextX][nextY][0]) {
                    dp[nextX][nextY][0] = nextP;
                    q.push({ {nextX, nextY}, {0, nextP} });
                }
            }
        }
    }
    return min(dp[N - 1][N - 1][0], dp[N - 1][N - 1][1]);
}
