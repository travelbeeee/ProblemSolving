/*
  BFS탐색
  
  이 문제처럼 안전지역으로 넘어갈 때 cost가 들지 않으면
  if (curL > visited[cur.first][cur.second]) continue;
  를 추가해줘서 겹치는 경우를 날려줘야된다!
  
*/
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int INF = 99999999;
const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
int N, M;
int map[501][501];
int visited[501][501];

bool isInside(int x, int y) {
	return (0 <= x && x <= 500 && 0 <= y && y <= 500);
}

void changeArea(int x1, int y1, int x2, int y2, int value) {
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++)
			map[i][j] = value; // 죽음
}

void set(void) {
	for (int i = 0; i <= 500; i++)
		for (int j = 0; j <= 500; j++)
			visited[i][j] = INF;
}

void BFS() {
	queue<pair<pair<int, int>, int>> q;
	q.push({ {0, 0}, 0 });
	visited[0][0] = 0;

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int curL = q.front().second;

		q.pop();

		if (curL > visited[cur.first][cur.second]) continue;
		if (cur.first == 500 && cur.second == 500) continue;

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (map[nextX][nextY] == -2) continue; //죽음의지역
			if (map[nextX][nextY] == -1 && curL + 1 < visited[nextX][nextY]) { // 위험구역
				visited[nextX][nextY] = curL + 1;
				q.push({ {nextX, nextY}, curL + 1 });
			}
			if (map[nextX][nextY] == 0 && curL < visited[nextX][nextY]) {
				visited[nextX][nextY] = curL;
				q.push({ {nextX, nextY}, curL });
			}
		}
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	set();

	cin >> N;
	for (int i = 0, x1, x2, y1, y2; i < N; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		changeArea(min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2), -1);
	}
	cin >> M;
	for (int i = 0, x1, x2, y1, y2; i < M; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		changeArea(min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2), -2);
	}

	BFS();

	visited[500][500] == INF ? (cout << -1 << '\n') : (cout << visited[500][500] << '\n');

	return 0;
}
