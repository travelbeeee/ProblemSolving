/*
	BFS탐색

	현재 내가 있는 지점(i, j)에서 갈 수 있는 방향은 대각선으로 4방향!
	
	왼쪽 위 / 오른쪽 위 / 왼쪽 아래 / 오른쪽 아래 ( dx, dy 로 표현 )
	그때 circuit이 어떤 상태냐에 따라 회전시키고 가야되는지
	회전없이 가는지가 정해진다. ( cx, cy 로 표현 )

*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int INF = 99999999;
int N, M;
int cx[4] = { -1, -1, 0, 0 }, cy[4] = { -1, 0, 0, -1 };
int dx[4] = { -1, -1, 1, 1 }, dy[4] = { -1, 1, 1, -1 };
int dp[501][501];
string circuit[500];

bool isInside(int x, int y) {
	return (0 <= x && x <= N && 0 <= y && y <= M);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> circuit[i];

	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= M; j++)
			dp[i][j] = INF;

	queue<pair<pair<int, int>, int>> q;
	q.push({ {0, 0}, 0 });
	dp[0][0] = 0;

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int curL = q.front().second;
		q.pop();

		if (cur.first == N && cur.second == M) continue;

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			int checkX = cur.first + cx[i], checkY = cur.second + cy[i];

			if (!isInside(nextX, nextY)) continue; // 내가 이동할 지점이 범위 밖
			if (i % 2) { // '/' 로 되어있으면 회전x
				if (circuit[checkX][checkY] == '/' && curL < dp[nextX][nextY]) {
					dp[nextX][nextY] = curL;
					q.push({ {nextX, nextY}, curL });
				}
				else if (circuit[checkX][checkY] == '\\' && curL + 1 < dp[nextX][nextY]) {
					dp[nextX][nextY] = curL + 1;
					q.push({ {nextX, nextY}, curL + 1 });
				}
			}
			else { // '\' 로 되어있으면 회전 x
				if (circuit[checkX][checkY] == '\\' && curL < dp[nextX][nextY]) {
					dp[nextX][nextY] = curL;
					q.push({ {nextX, nextY}, curL });
				}
				else if (circuit[checkX][checkY] == '/' && curL + 1 < dp[nextX][nextY]) {
					dp[nextX][nextY] = curL + 1;
					q.push({ {nextX, nextY}, curL + 1 });
				}
			}
		}
	}
	if (dp[N][M] == INF) cout << "NO SOLUTION\n";
	else cout << dp[N][M] << '\n';

	return 0;
}
