/*
    row : N행, col : M열 이라고 생각하자!
    (N, M) 에서 시작해서 (1, 1)로 역으로 DFS + DP 탐색을 진행하자.
*/
#include <string>
#include <vector>

using namespace std;

const int MOD = 1000000007;
const int dx[2] = { -1, 0 }, dy[2] = { 0, -1 };
int dp[101][101];
bool isCanGo[101][101];

void set(int m, int n, vector<vector<int>> puddles) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            isCanGo[i][j] = true, dp[i][j] = -1;
    for (int i = 0; i < puddles.size(); i++)
        isCanGo[puddles[i][1]][puddles[i][0]] = false;

}

bool isInside(int x, int y, int n, int m) {
    return (1 <= x && x <= n && 1 <= y && y <= m);
}

int DFS(int x, int y, int n, int m) {
    if (dp[x][y] != -1) return dp[x][y];
    if (x == 1 && y == 1) return 1;

    dp[x][y] = 0;

    for (int i = 0; i < 2; i++) {
        int nextX = x + dx[i], nextY = y + dy[i];
        if (!isInside(nextX, nextY, n, m)) continue;
        if (!isCanGo[nextX][nextY]) continue;
        dp[x][y] = (dp[x][y] + DFS(nextX, nextY, n, m)) % MOD;
    }

    return dp[x][y] % MOD;
}

int solution(int m, int n, vector<vector<int>> puddles) {
    set(m, n, puddles);

    DFS(n, m, n, m);
    
    return dp[n][m];
}
