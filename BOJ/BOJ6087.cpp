/*
	BFS탐색

	# visited[i][j][d] := (i, j)에 d 방향 상태로 왔을 때 필요한 최소 거울 개수

	1) 첫 번째 레이저 포인트 'C' 에서는 모든 방향으로 나아갈 수 있으므로 4개의 방향에 대해 초기 셋팅을 한다.
	2) 3가지 행동을 할 수 있다.
		- 현재 방향으로 한 칸 전진.
		- 현재 방향으로 한 칸 전진 && 거울에 의해 시계 방향으로 90도 회전.
		- 현재 방향으로 한 칸 전진 && 거울에 의해 반시계 방향으로 90도 회전.
		--> 3가지 행동에 대해서 가능한 경우라면 추가 탐색을 진행.

*/
#include<iostream>
#include<queue>
#include<algorithm>
	
using namespace std;

int H, W;
int visited[100][100][4];
char map[100][101];

const int INF = 999999;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };

bool isInside(int x, int y) {
	return (0 <= x && x < H && 0 <= y && y < W);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> W >> H;
	for (int i = 0; i < H; i++)
		cin >> map[i];

	// { { 좌표 }, { 방향, 거울개수 } }
	queue<pair<pair<int, int>, pair<int, int>>> q;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			for (int k = 0; k < 4; k++)
				visited[i][j][k] = INF;

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++) {
			if (map[i][j] == 'C') {
				for (int k = 0; k < 4; k++){
					q.push({ {i, j},  {k, 0} });
					visited[i][j][k] = 0;
				}
				map[i][j] = '.';
				i = H, j = W;
			}
		}

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int curD = q.front().second.first;
		int curM = q.front().second.second;

		q.pop();

		if (map[cur.first][cur.second] == 'C')	continue;
		if (visited[cur.first][cur.second][curD] < curM) continue;

		int nextM[3] = { curM, curM + 1, curM + 1 };
		int nextD[3] = { curD, (curD + 1) % 4, ((curD - 1) + 4) % 4 };

		for (int i = 0; i < 3; i++) {
			int nextX = cur.first + dx[nextD[i]], nextY = cur.second + dy[nextD[i]];
			if (isInside(nextX, nextY) && map[nextX][nextY] != '*' && nextM[i] < visited[nextX][nextY][nextD[i]]) {
				visited[nextX][nextY][nextD[i]] = nextM[i];
				q.push({ { nextX, nextY } , { nextD[i], nextM[i]} });
			}
		}
	}

	int ans = INF;
	for (int i = 0; i < H; i++)
		for(int j = 0; j < W; j++)
			if (map[i][j] == 'C') {
				for (int k = 0; k < 4; k++)
					ans = min(ans, visited[i][j][k]);
			}

	cout << ans << '\n';

	return 0;
}
