/*
  BFS탐색  BFS탐색
*/
#include<vector>
#include<queue>

using namespace std;

int solution(vector<vector<int>> maps) {
    const int INF = 99999999;
    const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
    int visited[100][100] = {};

    int N = maps.size(), M = maps[0].size();
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            visited[i][j] = INF;
    
    queue<pair<pair<int, int>, int>> q;
    q.push({ {0, 0}, 1 });
    visited[0][0] = 1;
    while (!q.empty()) {
        pair<int, int> cur = q.front().first;
        int curL = q.front().second;
        q.pop();
        
        if (cur.first == N - 1 && cur.second == M - 1) continue;
        if (visited[cur.first][cur.second] < curL) continue;
        
        for (int i = 0; i < 4; i++) {
            int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
            if (!(0 <= nextX && nextX < N && 0 <= nextY && nextY < M)) continue;
            if (visited[nextX][nextY] <= curL + 1) continue; // 최단거리존재
            if (maps[nextX][nextY] == 0) continue; // 벽

            visited[nextX][nextY] = curL + 1;
            q.push({ {nextX, nextY}, curL + 1 });
        }
    }
    int answer = visited[N - 1][M - 1];
    if (answer == INF) answer = -1;
    return answer;
}
