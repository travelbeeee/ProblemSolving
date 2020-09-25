/*
	전형적인 BFS 문제

	visited[x][y][d] := (x, y) 지점에 d 방향을 바라보고 있을 때 최소 이동 횟수
*/
#include<iostream>
#include<queue>

using namespace std;

const int INF = 99999999;

int N, M;
int map[101][101];
int visited[101][101][4];
int gX, gY, gD;
int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0};

struct step {
	int x, y, d;
};

bool isInside(int x, int y) {
	return (1 <= x && x <= N && 1 <= y && y <= M);
}

// 동쪽 0 남쪽 1 서쪽 2 북쪽 3 이라고 생각하자.
int changeDir(int x) {
	if (x == 1) return 0;
	else if (x == 2) return 2;
	else if (x == 3) return 1;
	return 3;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> map[i][j];
	for (int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			for (int d = 0; d < 4; d++)
				visited[i][j][d] = INF;

	int sX, sY, sD;
	cin >> sX >> sY >> sD >> gX >> gY >> gD;
	
	sD = changeDir(sD);
	gD = changeDir(gD);

	queue<step> q;
	q.push({ sX, sY, sD });
	visited[sX][sY][sD] = 0;

	while (!q.empty()) {
		int curX = q.front().x, curY = q.front().y, curD = q.front().d;
		q.pop();

		if (curX == gX && curY == gY && curD == gD) break;

		int nextX, nextY, nextD;
		// 왼쪽회전
		nextD = curD - 1;
		if (nextD == -1) nextD = 3;
		if (visited[curX][curY][curD] + 1 < visited[curX][curY][nextD]) {
			visited[curX][curY][nextD] = visited[curX][curY][curD] + 1;
			q.push({ curX, curY, nextD });
		}
		// 오른쪽 회전
		nextD = (curD + 1) % 4;
		if (visited[curX][curY][curD] + 1 < visited[curX][curY][nextD]) {
			visited[curX][curY][nextD] = visited[curX][curY][curD] + 1;
			q.push({ curX, curY, nextD });
		}
		// 현재 방향으로 1,2,3칸 이동
		nextX = curX, nextY = curY;
		for (int i = 0; i < 3; i++) {
			nextX += dx[curD], nextY += dy[curD];
			if (!isInside(nextX, nextY)) break;
			if (map[nextX][nextY] == 1) break;
			if (visited[curX][curY][curD] + 1 < visited[nextX][nextY][curD]) {
				visited[nextX][nextY][curD] = visited[curX][curY][curD] + 1;
				q.push({ nextX, nextY, curD });
			}
		}
	}

	visited[gX][gY][gD] == INF ? (cout << -1 << '\n') : (cout << visited[gX][gY][gD] << '\n');
	
	return 0;
}
