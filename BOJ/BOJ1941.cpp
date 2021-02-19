/*
	Backtraking BFS

	1) 백트레킹을 통해 5x5에서 7명을 뽑는 모든 경우의 수를 구한다.
		( 25C7 로 경우의 수가 그렇게 많지 않다.)

	2) 7명을 뽑고 BFS 탐색을 통해 7명이 서로 붙어있는지 체크한다.

	3) 서로 붙어있다면 'S', 'Y'를 count해서 원하는 답인지 체크한다.

*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int ans;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
string map[5];
vector<pair<int, int>> princess;

bool isInside(int x, int y) {
	return (0 <= x && x < 5 && 0 <= y && y < 5);
}

bool BFS(void) {
	bool check[5][5] = {}; // 7명의 공주들의 위치
	bool visited[5][5] = {};
	for (int i = 0; i < 7; i++)
		check[princess[i].first][princess[i].second] = true;

	queue<pair<int, int>> q;
	q.push({ princess[0].first, princess[0].second });
	visited[princess[0].first][princess[0].second] = true;

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (visited[nextX][nextY]) continue;
			if (!check[nextX][nextY]) continue;
			visited[nextX][nextY] = true;
			q.push({ nextX, nextY });
		}
	}
	for (int i = 0; i < 7; i++)
		if (!visited[princess[i].first][princess[i].second]) return false;
	return true;
}

void backtracking(int r, int c) {
	if ((int)princess.size() == 7) {
		if (!BFS()) return;
		int S = 0, Y = 0;
		for (int i = 0; i < 7; i++)
			if (map[princess[i].first][princess[i].second] == 'S') S++;
			else Y++;
		if (S >= 4) ans++;
		return;
	}
	for (int i = r; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == r && j < c) continue;
			princess.push_back({ i, j });
			backtracking(i + (((j + 1) % 5) == 0), (j + 1) % 5);
			princess.pop_back();
		}
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	for (int i = 0; i < 5; i++)
		cin >> map[i];

	backtracking(0, 0);

	cout << ans << '\n';

	return 0;
}
