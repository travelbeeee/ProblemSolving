/*
  단순 BFS
*/
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

struct box {
	int x1, y1, x2, y2, l;
};

const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
int N, M;
bool visited[20][20][20][20];
string map[20];
vector<pair<int, int>> coin;
queue<box> q;

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < M);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> map[i];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == 'o') {
				coin.push_back({ i, j });
				map[i][j] = '.';
			}

	q.push({ coin[0].first, coin[0].second, coin[1].first, coin[1].second, 0 });
	visited[coin[0].first][coin[0].second][coin[1].first][coin[1].second] = true;
	
	int ans = 99999999;
	while (!q.empty()) {
		box cur = q.front();
		q.pop();

		if (cur.l >= 10) continue;

		for (int i = 0; i < 4; i++) {
			int nextX1 = cur.x1 + dx[i], nextX2 = cur.x2 + dx[i], nextY1 = cur.y1 + dy[i], nextY2 = cur.y2 + dy[i];
			if (isInside(nextX1, nextY1) && map[nextX1][nextY1] == '#'){
				nextX1 -= dx[i], nextY1 -= dy[i];
			}
			if (isInside(nextX2, nextY2) && map[nextX2][nextY2] == '#'){
				nextX2 -= dx[i], nextY2 -= dy[i];
			}
			
			// 둘다 보드 바깥
			if (!isInside(nextX1, nextY1) && !isInside(nextX2, nextY2)) continue;
			// 하나만 바깥으로! 게임 끝! --> 답 갱신
			if ((!isInside(nextX1, nextY1) && isInside(nextX2, nextY2))
				|| (isInside(nextX1, nextY1) && !isInside(nextX2, nextY2))) {
				ans = min(ans, cur.l + 1);
				continue;
			}
			// 게임 마저 진행
			if (visited[nextX1][nextY1][nextX2][nextY2]) continue;
			visited[nextX1][nextY1][nextX2][nextY2] = true;
			q.push({ nextX1, nextY1, nextX2, nextY2, cur.l + 1 });
		}
	}
	
	(ans == 99999999) ? (cout << -1 << '\n') : (cout << ans << '\n');

	return 0;
}
