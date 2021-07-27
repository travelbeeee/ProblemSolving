/*
	BFS 탐색 + DP

	'0' 인 부분에서 BFS 탐색을 진행하자.

	'1'(벽) 에서 벽을 허물고 이동할 수 있는 칸의 개수
	= 자기 자리 + 인접한 칸 중 '0'인 칸에서의 최대 탐색 칸 수
	--> '0' 인 부분에서 BFS 탐색을 진행하면서 인접한 벽에다가 BFS 탐색 결과로 나온 탐색 칸의 수를 저장하자.
*/
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int n, m;
int ansMap[1000][1000];
string map[1000];
bool visited[1000][1000];

const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, -1, 0, 1 };

bool isInside(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

void BFS(int x, int y) {
	queue<pair<int, int>> q;
	vector<pair<int, int>> wall;
	int size = 1;
	q.push({ x, y });
	visited[x][y] = 1;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nextX = cur.first + dx[dir], nextY = cur.second + dy[dir];
			if (!isInside(nextX, nextY)) continue;
			if (visited[nextX][nextY]) continue;
			if (map[nextX][nextY] == '1') {
				wall.push_back({ nextX, nextY });
				continue;
			}
			q.push({ nextX, nextY });
			visited[nextX][nextY] = 1;
			size++;
		}
	}
	sort(wall.begin(), wall.end());
	wall.erase(unique(wall.begin(), wall.end()), wall.end());
	for (pair<int, int> w : wall) {
		ansMap[w.first][w.second] += size;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> map[i];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == '0' && !visited[i][j])
				BFS(i, j);
			if (map[i][j] == '1')
				ansMap[i][j]++;
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << ansMap[i][j] % 10;
		}
		cout << '\n';
	}
	
	return 0;
}
