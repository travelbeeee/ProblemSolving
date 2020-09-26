/*
	# 백트레킹
	백트레킹을 이용해 빈 공간에 벽을 3개 생성하는 모든 경우의 수에 대해서
	BFS 탐색을 통해 바이러스를 퍼뜨리고 안전 영역을 구해 답을 갱신한다.
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int r, c, ans = 0;
int map[8][8];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

bool isInside(int x, int y) {
	return (0 <= x && x < r && 0 <= y && y < c);
}

int getSafeArea(void) {
	// '2' 바이러스에서 다 퍼뜨려보자.
	queue<pair<int, int>> virus;
	int tempMap[8][8] = {};
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++){
			tempMap[i][j] = map[i][j];
			if (tempMap[i][j] == 2) virus.push({ i, j });
		}

	while (!virus.empty()) {
		int curX = virus.front().first, curY = virus.front().second;
		virus.pop();
		for (int i = 0; i < 4; i++) {
			int nextX = curX + dx[i], nextY = curY + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (tempMap[nextX][nextY] != 0) continue;
			tempMap[nextX][nextY] = 2;
			virus.push({ nextX, nextY });
		}
	}

	int area = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			if (tempMap[i][j] == 0) area++;
	return area;
}

void backtracking(int wallCnt) {
	if (wallCnt == 3) {
		ans = max(ans, getSafeArea());
		return;
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 1;
				backtracking(wallCnt + 1);
				map[i][j] = 0;
			}
		}
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> r >> c;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			cin >> map[i][j];

	backtracking(0);

	cout << ans << '\n';
}
