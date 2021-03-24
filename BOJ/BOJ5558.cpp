/*
  1번 치즈부터 차례대로 N번 치즈까지 BFS탐색!
*/
#include<iostream>
#include<queue>

using namespace std;

int H, W, N;
int sX, sY;
string map[1000];

int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

bool isInside(int x, int y) {
	return (0 <= x && x < H && 0 <= y && y < W);
}

// (sX, sY)에서 goal 치즈를 찾는데 걸리는 최단 거리
int BFS(int goal) {
	queue<pair<pair<int, int>, int>> q;
	bool visited[1000][1000] = {};

	q.push({ {sX, sY}, 0 });
	visited[sX][sY] = true;

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int length = q.front().second;
		q.pop();
		if ((map[cur.first][cur.second] - '0') == goal) {
			sX = cur.first, sY = cur.second;
			return length;
		}

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (visited[nextX][nextY]) continue;
			if (map[nextX][nextY] == 'X') continue;

			q.push({ { nextX, nextY}, length + 1 });
			visited[nextX][nextY] = true;
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> H >> W >> N;
	for (int i = 0; i < H; i++)
		cin >> map[i];
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			if (map[i][j] == 'S') {
				map[i][j] = '.';
				sX = i, sY = j;
			}

	int ans = 0;
	for (int i = 1; i <= N; i++)
		ans += BFS(i);
	cout << ans << '\n';

	return 0;
}
