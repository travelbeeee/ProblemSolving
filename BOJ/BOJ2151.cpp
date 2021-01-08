/*
	BFS탐색 

	양면 거울을 쓸 일이 있나...?
	같은 거울을 2번 이용해야되는 상황은 한 번만 이용해서 해결 가능
	--> 거울을 설치했으면 한 번만 쓴다고 가정하고 BFS 탐색으로 진행하자.

	1) 현재 위치(i, j) 현재 방향 d 정보를 가지고 탐색을 진행.
	현재 상태에서 몇 개의 거울을 지나쳐왔는지 정보를 위해 visited 배열을 int 로 선언.
	
	2) 현재 위치(i, j) 현재 방향 d 에서 이전에 지금 거울의 수 m 보다 작은 값으로 탐색한 경우 --> 더 탐색 X
	--> visited[i][j][d] = m 으로 설정하자!

*/
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int INF = 2501;
int N, ans;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };
char map[50][51];
queue<pair<pair<int, int>, int>> q;
int visited[50][50][4]; // visited[i][j][k] (i, j)에 방향 k를 가지고 도착한 최소 거울 이용 수

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < N);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> map[i];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < 4; k++)
				visited[i][j][k] = INF;
	ans = INF;

	for (int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if (map[i][j] == '#') {
				map[i][j] = '.';
				for (int k = 0; k < 4; k++){
					q.push({ {i, j}, k });
					visited[i][j][k] = 0;
				}
				i = N, j = N;
			}

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int curD = q.front().second;
		int curM = visited[cur.first][cur.second][curD];

		q.pop();

		int nextX = cur.first + dx[curD], nextY = cur.second + dy[curD];

		if (!isInside(nextX, nextY)) continue;
		if (map[nextX][nextY] == '*') continue;

		if (map[nextX][nextY] == '#') // 끝
			ans = min(ans, curM);
		else if (map[nextX][nextY] == '!') {
			// 거울 '/' 설치
			int nextD;
			if (curD == 0) nextD = 1;
			else if (curD == 1) nextD = 0;
			else if (curD == 2) nextD = 3;
			else nextD = 2;
				
			if (visited[nextX][nextY][nextD] < curM + 1) continue;
			q.push({ { nextX, nextY}, nextD });
			visited[nextX][nextY][nextD] = curM + 1;

			// 거울 '\' 설치
			if (curD == 0) nextD = 3;
			else if (curD == 1) nextD = 2;
			else if (curD == 2) nextD = 1;
			else nextD = 0;

			if (visited[nextX][nextY][nextD] < curM + 1) continue;
			q.push({ { nextX, nextY}, nextD});
			visited[nextX][nextY][nextD] = curM + 1;

			// 그냥 이동
			if (visited[nextX][nextY][curD] < curM) continue;
			visited[nextX][nextY][curD] = curM;
			q.push({ {nextX, nextY}, curD });
		}
		else{ // '.'
			if (visited[nextX][nextY][curD] < curM) continue;
			visited[nextX][nextY][curD] = curM;
			q.push({ {nextX, nextY}, curD });
		}
	}
	cout << ans << '\n';

	return 0;
}
