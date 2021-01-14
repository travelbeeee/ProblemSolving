/*
	BFS + DP

	BFS탐색을 진행하는데 기존 경로 좌표와 최소로 건너온 타일 횟수를 DP에 저장하면서 넘어간다.
	
	좌표에 따라 TileNum 을 얻는 부분을 제외하고 
	전형적인 기존 경로를 저장하는 BFS탐색으로 까다로운 부분은 없는데....
	정말 정말 많이 틀렸다...

	[ 많이많이틀린이유 ]
	경로를 출력할 때 타일번호를 정렬해서 출력한다고 생각했음
	--> 문제에 그냥 경로를 출력하라고 되어있지 타일번호를 정렬하라고는 안되어있다!!!!!!!!

*/
#include<iostream>
#include<queue>

using namespace std;

int N;
int map[500][1000];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };
pair<int, pair<int, int>> dp[500][1000];

const int INF = 99999999;

void set(void) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 2 * N; j++)
			dp[i][j] = { INF, {0, 0} };
}

int getTileNum(int x, int y) {
	return (2 * N - 1) * (x / 2) + N * (x % 2) + ((y - (x % 2)) / 2) + 1;
}

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < 2 * N);
}

void BFS(void) {
	queue<pair<pair<int, int>, int>> q;
	q.push({ {0, 0}, 1 });
	dp[0][0] = { 1, {-1, -1} };

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int curL = q.front().second;
		q.pop();
		if (dp[cur.first][cur.second].first != curL) continue;

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];

			if (!isInside(nextX, nextY)) continue;
			if (map[nextX][nextY] == 0) continue;

			int curTileNum = getTileNum(cur.first, cur.second);
			int nextTileNum = getTileNum(nextX, nextY);

			if (curTileNum == nextTileNum) {
				if (curL < dp[nextX][nextY].first) {
					dp[nextX][nextY] = { curL, { cur.first, cur.second} };
					q.push({ {nextX, nextY}, curL });
				}
			}
			else {
				if (map[cur.first][cur.second] == map[nextX][nextY] &&
					curL + 1 < dp[nextX][nextY].first) {
					dp[nextX][nextY] = { curL + 1, { cur.first, cur.second} };
					q.push({ {nextX, nextY}, curL + 1 });
				}
			}
		}
	}
}
void getAnswer(void) {
	for (int i = N - 1; i >= 0; i--) {
		for (int j = 2 * N - (i % 2) - 1; j >= 0; j--) {
			if (dp[i][j].first != INF) { // 여기 타일까지 도달했음!
				vector<int> tiles;
				pair<int, int> cur = { i, j };
				while (1) {
					if (dp[cur.first][cur.second].second.first == -1)
						break;
					tiles.push_back(getTileNum(cur.first, cur.second));
					cur = dp[cur.first][cur.second].second;
				}

				cout << dp[i][j].first << '\n';
				for (int i = (int)tiles.size() - 1; i >= 0; i--)
					if (i == 0 || tiles[i] != tiles[i - 1]) cout << tiles[i] << ' ';

				return;
			}
		}
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++)
		for (int j = 0 + (i % 2); j < 2 * N - (i % 2); j++)
			cin >> map[i][j];

	// BFS 셋팅값
	set();
	
	// BFS로 최대한 탐색
	BFS();

	// 정답 출력
	getAnswer();


	return 0;
}
