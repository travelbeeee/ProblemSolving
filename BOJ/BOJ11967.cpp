/*
	BFS탐색을 한 번만 수행하면 안된다.
	현재 BFS 탐색을 수행하고 새롭게 전구가 켜진 변화가 있다면
	다시 BFS 탐색을 처음부터 다시 수행해본다.

*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M, x, y, a, b;
bool light[101][101];
vector<pair<int, int>> map[101][101];

bool isInside(int x, int y) {
	return (1 <= x && x <= N && 1 <= y && y <= N);
}

void BFS() {
	queue<pair<int, int>> q;
	int dx[4] = { -1,0,1,0 }, dy[4] = { 0, -1, 0, 1 };
	bool visited[101][101] = {};

	q.push({ 1, 1 });
	visited[1][1] = true;
	
	int newLight = 0;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		// 불을 켜자
		for (int i = 0; i < map[cur.first][cur.second].size(); i++) {
			pair<int, int> next = map[cur.first][cur.second][i];
			if (!light[next.first][next.second]) newLight++;
			light[next.first][next.second] = true;
		}

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (!light[nextX][nextY]) continue;
			if (visited[nextX][nextY]) continue;

			visited[nextX][nextY] = true;
			q.push({ nextX, nextY });
		}
	}
	if (newLight) BFS();

	return;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> a >> b;
		map[x][y].push_back({ a, b });
	}
	
	light[1][1] = true;

	BFS();

	int ans = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (light[i][j]) ans++;

	cout << ans << '\n';

	return 0;
}
