/*
  DP + BFS탐색 + Bitmasking
  
  목적지가 2개 뿐이므로 Bitmasking을 이용한다!
  또, 방향도 중요한 요소이므로 방향도 요소로 넘겨준다.
*/
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

const int INF = 9999;
const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
int N, M, sX, sY;
int dp[50][50][4][4]; // dp[x][y][dir][status] (x,y) 좌표에 dir 방향으로 status로 도착
string map[50];

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < M);
}

void setting(void) {
	bool isFirst = true;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 'S') {
				sX = i, sY = j;
				map[i][j] = '.';
			}
			if (isFirst && map[i][j] == 'C') {
				map[i][j] = '0';
				isFirst = false;
			}
			if (!isFirst && map[i][j] == 'C') {
				map[i][j] = '1';
			}
			for (int k = 0; k < 4; k++)
				for (int l = 0; l < 4; l++)
					dp[i][j][k][l] = INF;
		}
	}
}

struct box {
	int x, y, d, s, l;
};

int BFS(void) {
	int ans = INF, goal = 3;
	queue<box> q;
	// 4가지 방향으로 다 진행할거므로 다 추가하자
	for (int i = 0; i < 4; i++) {
		dp[sX][sY][i][0] = 0;
		q.push({ sX, sY, i, 0, 0 });
	}
	while (!q.empty()) {
		box cur = q.front();
		q.pop();
		if (cur.s == goal) { // 비트마스트 11 이므로 C를 다들림!
			ans = min(ans, cur.l);
			continue;
		}

		for (int i = 0; i < 4; i++) {
			if (i == cur.d) continue;
			int nextX = cur.x + dx[i], nextY = cur.y + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (map[nextX][nextY] == '#') continue;

			if (map[nextX][nextY] == '.' && cur.l + 1 < dp[nextX][nextY][i][cur.s]) {
				dp[nextX][nextY][i][cur.s] = cur.l + 1;
				q.push({ nextX, nextY, i, cur.s, cur.l + 1 });
			}
			if (map[nextX][nextY] != '.') {
				int nextS = cur.s | (1 << map[nextX][nextY] - '0');
				if (cur.l + 1 < dp[nextX][nextY][i][nextS]) {
					dp[nextX][nextY][i][nextS] = cur.l + 1;
					q.push({ nextX, nextY, i, nextS, cur.l + 1 });
				}
			}
		}
	}
	return (ans == INF) ? -1 : ans;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> map[i];

	setting(); 

	cout << BFS() << '\n';;

	return 0;
}
