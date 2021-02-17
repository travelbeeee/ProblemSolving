/*
	BFS탐색

	통나무의 중간 지점과 가로/세로 모양만 알고있으면 모든 이동과 회전에 대해서 체크가 가능하다.
  
	1) 통나무 중간 지점을 상하좌우로 이동시킨 후 모양에 맞춰서 이동 가능한지 체크한다.
	2) 통나무 중간 지점을 기점으로 3x3 칸들을 모두 체크 후 회전 가능한지 체크한다.

*/
#include<iostream>
#include<queue>

using namespace std;

const int INF = 9999;
int N, dp[50][50][2];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
pair<pair<int, int>, bool> tree[2]; // 중간 지점과 모양을 저장하자
string map[50];

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < N);
}

void setPoint(char c, bool b) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == c) {
				if (isInside(i, j + 1) && isInside(i, j + 2)
					&& map[i][j + 1] == c && map[i][j + 2] == c) {
					tree[b] = { {i, j + 1}, false };
					map[i][j] = map[i][j + 1] = map[i][j + 2] = '0';
				}
				if (isInside(i + 1, j) && isInside(i + 2, j)
					&& map[i + 1][j] == c && map[i + 2][j] == c) {
					tree[b] = { {i + 1, j }, true };
					map[i][j] = map[i + 1][j] = map[i + 2][j] = '0';
				}
			}
		}
	}
}

void setDp(void) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dp[i][j][0] = dp[i][j][1] = INF;
}

bool isCanGo(int x, int y, int d) {
	if (d == 0 && isInside(x, y - 1) && isInside(x, y + 1) && isInside(x, y) && map[x][y] == '0' && map[x][y - 1] == '0' && map[x][y + 1] == '0')
		return true;
	if (d == 1 && isInside(x - 1, y) && isInside(x + 1, y) && isInside(x, y) && map[x][y] == '0' && map[x - 1][y] == '0' && map[x + 1][y] == '0')
		return true;
	return false;
}

bool isCanTranslate(int x, int y) {
	int tX[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 }, tY[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
	for (int i = 0; i < 9; i++) {
		int nX = x + tX[i], nY = y + tY[i];
		if (!isInside(nX, nY)) return false;
		if (map[nX][nY] == '1') return false;
	}
	return true;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> map[i];

	// 시작지점과 끝지점 설정
	setPoint('B', 0);
	setPoint('E', 1);
	// dp배열 초기화
	setDp();

	queue<pair<pair<int, int>, pair<int, bool>>> q;
	q.push({ {tree[0].first.first, tree[0].first.second}, {0, tree[0].second} });
	dp[tree[0].first.first][tree[0].first.second][tree[0].second] = 0;

	// dir이 0이면 가로로 1이면 세로로 놓여져있는상황
	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int cnt = q.front().second.first;
		bool dir = q.front().second.second;
		q.pop();

		if (tree[1].first.first == cur.first && tree[1].first.second == cur.second && tree[1].second == dir)
			continue;

		// 상 하 좌 우 로 이동시켜보자.
		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isCanGo(nextX, nextY, dir)) continue;
			if (dp[nextX][nextY][dir] <= cnt + 1) continue;
			q.push({ {nextX, nextY}, {cnt + 1, dir } });
			dp[nextX][nextY][dir] = cnt + 1;
		}
		// 90도 회전
		if (!isCanTranslate(cur.first, cur.second)) continue;
		if (dp[cur.first][cur.second][!dir] <= cnt + 1) continue;
		q.push({ {cur.first, cur.second}, {cnt + 1, !dir } });
		dp[cur.first][cur.second][!dir] = cnt + 1;
	}

	if (dp[tree[1].first.first][tree[1].first.second][tree[1].second] == INF) cout << "0\n";
	else cout << dp[tree[1].first.first][tree[1].first.second][tree[1].second] << '\n';

	return 0;
}
