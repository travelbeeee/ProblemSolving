/*
	BFS탐색

	어차피 벽은 8번 이동 후에는 다 사라짐!
	--> 8초까지 모든 벽의 상태를 저장하자.
		&& 8초까지 visited 배열을 모두 따로 가지고 있자!

*/
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

bool ans;
char map[9][8][9];
bool visited[9][8][8];
int dx[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1}, dy[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1};

void init(void) {
	for (int k = 0; k < 9; k++)
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				map[k][i][j] = '.';
}

void setMap(void) {
	for (int k = 1; k < 8; k++)
		for (int i = 7; i >= 0; i--)
			for (int j = 0; j < 8; j++)
				if (map[k - 1][i][j] == '#') {
					if (i == 7) continue;
					map[k][i + 1][j] = '#';
				}
}

bool isInside(int x, int y) {
	return (0 <= x && x < 8 && 0 <= y && y < 8);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	init();

	for (int i = 0; i < 8; i++)
		cin >> map[0][i];

	setMap();

	queue<pair<pair<int, int>, int>> q;
	q.push({ {7, 0}, 0 });
	visited[0][7][0] = true;

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int t = q.front().second;
		q.pop();

		if (map[t][cur.first][cur.second] == '#') continue;

		if (cur.first == 0 && cur.second == 7) {
			ans = true;
			break;
		}

		for (int i = 0; i < 9; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (map[t][nextX][nextY] == '#') continue;

			if (t != 8 && !visited[t + 1][nextX][nextY]) {
				visited[t + 1][nextX][nextY] = true;
				q.push({ {nextX, nextY}, t + 1 });
			}
			else if(t == 8 && !visited[t][nextX][nextY]){
				visited[t][nextX][nextY] = true;
				q.push({ {nextX, nextY}, t });
			}
		}
	}

	ans ? (cout << "1\n") : (cout << "0\n");

	return 0;
}
