/*
	DP + BFS탐색
*/

#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

const int INF = 99999999;
int N, M, Hx, Hy, Ex, Ey;
bool map[1001][1001];
int visited[1001][1001][2];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

bool isInside(int x, int y) {
	return (1 <= x && x <= N && 1 <= y && y <= M);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> Hx >> Hy >> Ex >> Ey;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> map[i][j];
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			visited[i][j][0] = visited[i][j][1] = INF;

	queue<pair<pair<int, int>, pair<int, bool>>> q;
	q.push({ {Hx, Hy}, {0, 0} });
	visited[Hx][Hy][0] = 0;

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int curL = q.front().second.first;
		bool isBroken = q.front().second.second;
		q.pop();

		cout << cur.first << ' ' << cur.second << ' ' << curL << ' ' << isBroken << '\n';
		if (cur.first == Ex && cur.second == Ey) continue;

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (map[nextX][nextY] && !isBroken) { // 벽이고 부신 적 없음
				if (curL + 1 < visited[nextX][nextY][!isBroken]) {
					visited[nextX][nextY][!isBroken] = curL + 1;
					q.push({ {nextX, nextY},{curL + 1, !isBroken} });
				}
			}
			else if(!map[nextX][nextY]){ // 벽이 아님
				if (curL + 1 < visited[nextX][nextY][isBroken]) {
					visited[nextX][nextY][isBroken] = curL + 1;
					q.push({ {nextX, nextY}, {curL + 1, isBroken} });
				}
			}
		}
	}
	if (min(visited[Ex][Ey][0], visited[Ex][Ey][1]) == INF) cout << "-1\n";
	else cout << min(visited[Ex][Ey][0], visited[Ex][Ey][1]) << '\n';
	
	return 0;
}
