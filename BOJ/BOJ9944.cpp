/*
  완전탐색 (DFS)
  
  공을 놓을 수 있는 모든 곳에서 시작해서, 4방향 중 이동이 가능한 모든 방향으로 계속 탐색을 진행한다.
*/
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int INF = 99999999;
const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

int N, M, ans, testCase = 1, goal;
char map[30][31];
bool visited[30][30];

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < M);
}

void DFS(int curX, int curY, int curC, int curL) {
	if (curL >= ans) 
		return;

	if (curC == goal) {
		ans = min(ans, curL);
		return;
	}

	for (int dir = 0; dir < 4; dir++) {
		int nextX = curX + dx[dir], nextY = curY + dy[dir];
		if (!isInside(nextX, nextY)) continue;
		if (map[nextX][nextY] == '*') continue;

		int cnt = 0;
		while (true) {
			if (!isInside(nextX, nextY)) break;
			if (map[nextX][nextY] == '*') break;
			if (visited[nextX][nextY]) break;

			visited[nextX][nextY] = true;
			nextX += dx[dir], nextY += dy[dir];
			cnt++;
		}
		nextX -= dx[dir], nextY -= dy[dir];
		if (cnt == 0) continue;

		DFS(nextX, nextY, curC + cnt, curL + 1);

		// (curX, curY) --> (nextX, nextY) 까지 가면서 true로 만들었음
		while (true) {
			if (curX == nextX && curY == nextY) break;
			visited[nextX][nextY] = false;
			nextX -= dx[dir], nextY -= dy[dir];
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	while (cin >> N >> M) {
		for (int i = 0; i < N; i++)
			cin >> map[i];
		goal = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++){
				if (map[i][j] == '.') goal++;
				visited[i][j] = false;
			}
		}

		ans = INF;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < M; j++){
				if (map[i][j] == '.'){
					visited[i][j] = true;
					DFS(i, j, 1, 0);
					visited[i][j] = false;
				}
			}
		}

		if (ans == INF) ans = -1;
		cout << "Case " << testCase++ <<  ": " << ans << '\n';
	}

	return 0;
}
