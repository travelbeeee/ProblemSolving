/*
	BFS탐색

	X, Y좌표의 범위가 -500 ~ 500 이므로 최대 1001 * 1001 칸 밖에 사용을 안함.
	--> 직사각형의 한 점을 각각 그래프의 노드처럼 생각해서 양방향 그래프를 만들자.
	--> 그 후 BFS 탐색을 진행해서 한 번 탐색을 진행했을 때
		탐색이 되는 직사각형들은 거북이가 한 번에 그릴 수 있는 직사각형.
	그러면 최대 1001 * 1001 칸만 탐색하고 끝나므로 시간초과 문제 X
	--> 이게 Union-Find 보다 구현이 쉬울거라고 판단해서 진행함!

	[처음에 생각한 아이디어]

	Union-Find 로 서로 닿는 부분이 있는 직사각형들끼리 
	같은 set으로 묶어준다면 해결 할 수 있음.
	--> Union-Find 로도 한 번 도전해봐야겠다!
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

typedef struct rectangle {
	int x1, y1, x2, y2;
};

int N;
int dx[4] = { 1, 0, -1, 0}, dy[4] = { 0, 1, 0, -1 };
vector<pair<int, int>> map[1001][1001];

bool isInside(int x, int y) {
	return (0 <= x && x <= 1000 && 0 <= y && y <= 1000);
}

void draw(int x1, int y1, int x2, int y2) {
	int minX = min(x1, x2), maxX = max(x1, x2);
	int minY = min(y1, y2), maxY = max(y1, y2);

	queue<pair<pair<int, int>, int>> q;

	q.push({ {minX, minY},  0 });
	q.push({ {minX, minY}, 1 });

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int curD = q.front().second;
		q.pop();

		if (cur.first == maxX && cur.second == maxY) continue;

		int nextX = cur.first + dx[curD], nextY = cur.second + dy[curD];
		if (!isInside(nextX, nextY)) continue;

		if (curD == 0 && nextX == maxX) {
			q.push({ { nextX, nextY}, 1 });
		}
		else if (curD == 1 && nextY == maxY) {
			q.push({ {nextX, nextY}, 0 });
		}
		else {
			q.push({ { nextX, nextY }, curD });
		}
		map[cur.first][cur.second].push_back({ nextX, nextY });
		map[nextX][nextY].push_back({ cur.first, cur.second });
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0, x1, y1, x2, y2; i < N; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		x1 += 500, y1 += 500, x2 += 500, y2 += 500;
		draw(x1, y1, x2, y2);
	}

	queue<pair<int, int>> q;
	int ans = 0;
	bool visited[1001][1001] = {};

	for (int i = 0; i <= 1000; i++) {
		for (int j = 0; j <= 1000; j++) {
			if (map[i][j].empty()) continue;
			if (visited[i][j]) continue;

			q.push({ i, j });
			visited[i][j] = true;
			ans++;

			while (!q.empty()) {
				pair<int, int> cur = q.front();
				q.pop();
				if (cur.first == 500 && cur.second == 500) ans--;

				for (int k = 0; k < map[cur.first][cur.second].size(); k++) {
					int nextX = map[cur.first][cur.second][k].first;
					int nextY = map[cur.first][cur.second][k].second;

					if (visited[nextX][nextY]) continue;

					q.push({ nextX, nextY });
					visited[nextX][nextY] = true;
				}
			}
		}
	}

	cout << ans << '\n';

	return 0;
}
