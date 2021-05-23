#include<iostream>
#include<queue>

using namespace std;

const int INF = 9999999;
const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, -1, 0, 1 };

int N, M;
pair<int, int> visited[50][50];
string map[50];

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < M);
}

void set() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = { INF, INF };
	for (int i = 0; i < N; i++) // 쓰레기의 인접칸을 G로 바꾸자
		for (int j = 0; j < M; j++)
			if (map[i][j] == 'g') {
				for (int k = 0; k < 4; k++) {
					if (!isInside(i + dx[k], j + dy[k])) continue;
					if (map[i + dx[k]][j + dy[k]] == '.') map[i + dx[k]][j + dy[k]] = 'G';
				}
			}
}



void BFS() {
	queue<pair<pair<int, int>, pair<int, int>>> q;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == 'S') {
				q.push({ {i, j}, {0, 0} });
			}

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int garbageCnt = q.front().second.first;
		int garbageBesideCnt = q.front().second.second;
		q.pop();

		if (map[cur.first][cur.second] == 'F') continue;
		if (visited[cur.first][cur.second].first < garbageCnt) continue;
		if (visited[cur.first][cur.second].first == garbageCnt && visited[cur.first][cur.second].second < garbageBesideCnt) continue;

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (map[nextX][nextY] == 'g') {
				if (garbageCnt + 1 < visited[nextX][nextY].first ||
					(garbageCnt + 1 == visited[nextX][nextY].first &&
						garbageBesideCnt < visited[nextX][nextY].second)) {
					visited[nextX][nextY] = { garbageCnt + 1, garbageBesideCnt };
					q.push({ {nextX, nextY}, {garbageCnt + 1, garbageBesideCnt} });
				}
			}
			else if (map[nextX][nextY] == 'G') {
				if (garbageCnt < visited[nextX][nextY].first ||
					(garbageCnt == visited[nextX][nextY].first && garbageBesideCnt + 1 < visited[nextX][nextY].second)) {
					visited[nextX][nextY] = { garbageCnt, garbageBesideCnt + 1 };
					q.push({ { nextX, nextY}, {garbageCnt, garbageBesideCnt + 1} });
				}
			}
			else {
				if (garbageCnt < visited[nextX][nextY].first ||
					(garbageCnt == visited[nextX][nextY].first && garbageBesideCnt < visited[nextX][nextY].second)) {
					visited[nextX][nextY] = { garbageCnt, garbageBesideCnt };
					q.push({ {nextX, nextY}, {garbageCnt, garbageBesideCnt} });
				}
			}
		}
	}
}

void printAns() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == 'F') cout << visited[i][j].first << ' ' << visited[i][j].second << '\n';
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> map[i];

	set();

	BFS();

	printAns();

	return 0;
}
