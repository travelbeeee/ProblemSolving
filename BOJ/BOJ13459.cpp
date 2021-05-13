#include<iostream>
#include<queue>

using namespace std;

const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
int N, M;
string map[10];
bool visited[10][10][10][10];

// 현재위치에서 dir방향으로 구슬을 이동해서 이동한 위치를 반환해준다.
pair<int, int> moveMarble(pair<int, int> cur, int dir) {
	int nextX = cur.first, nextY = cur.second;
	while (1) {
		nextX += dx[dir], nextY += dy[dir];
		if (map[nextX][nextY] == '#') break;
		if (map[nextX][nextY] == 'O') return { nextX, nextY };
	}
	return { nextX - dx[dir], nextY - dy[dir] };
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> map[i];

	pair<int, int> red, blue;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == 'R') {
				red = { i, j };
				map[i][j] = '.';
			}
			else if (map[i][j] == 'B') {
				blue = { i, j };
				map[i][j] = '.';
			}

	queue<pair<pair<int, int>, pair<int, int>>> q;

	q.push({ red, blue });
	visited[red.first][red.second][blue.first][blue.second] = true;
	bool isRemoveRed = false;

	for (int move = 0; move <= 10; move++) {
		int qSize = q.size();
		for (int j = 0; j < qSize; j++) {
			pair<int, int> curR = q.front().first;
			pair<int, int> curB = q.front().second;

			q.pop();

			if (map[curR.first][curR.second] == 'O' && map[curB.first][curB.second] != 'O') {
				isRemoveRed = true;
				move = 11; // 이중브레이크
				break;
			}

			for (int dir = 0; dir < 4; dir++) {
				pair<int, int> nextR = moveMarble(curR, dir);
				pair<int, int> nextB = moveMarble(curB, dir);
				if (nextR.first == nextB.first && nextR.second == nextB.second) {
					if (map[nextR.first][nextR.second] == 'O') continue;
					if (dir == 0) {
						if (curR.first < curB.first) nextB.first -= dx[dir];
						else nextR.first -= dx[dir];
					}
					else if (dir == 1) {
						if (curR.second < curB.second) nextB.second -= dy[dir];
						else nextR.second -= dy[dir];
					}
					else if (dir == 2) {
						if (curR.first > curB.first) nextB.first -= dx[dir];
						else nextR.first -= dx[dir];
					}
					else {
						if (curR.second > curB.second) nextB.second -= dy[dir];
						else nextR.second -= dy[dir];
					}
				}

				if (visited[nextR.first][nextR.second][nextB.first][nextB.second]) continue;
				if (map[nextB.first][nextB.second] == 'O') continue;
                
				q.push({ nextR, nextB });
				visited[nextR.first][nextR.second][nextB.first][nextB.second] = true;
			}
		}
	}
	(isRemoveRed) ? (cout << 1 << '\n') : (cout << 0 << '\n');

	return 0;
}
