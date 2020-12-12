/*
	백트레킹

	1) 백트레킹을 통해 'X' 칸에 'O'(장애물) 을 3개 설치한다.
	2) 3개 설치된 Map에서 학생들이 감시를 피했는지 체크한다.

*/
#include<iostream>

using namespace std;

int N, dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
char map[6][7];
bool ans;

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < N);
}

bool check(void) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 'T') {
				for (int k = 0; k < 4; k++) {
					int nextX = i + dx[k], nextY = j + dy[k];
					while (isInside(nextX, nextY)) {
						if (map[nextX][nextY] == 'S') return false;
						if (map[nextX][nextY] != 'X') break;
						nextX += dx[k], nextY += dy[k];
					}
				}
			}
		}
	}
	return true;
}
void init(int k, int cnt) {
	if (ans) return;

	if (cnt == 3) {
		ans = check();
		return;
	}

	int r = k / N, c = k % N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i < r) continue;
			if (i == r && j < c) continue;
			if (map[i][j] != 'X') continue;

			map[i][j] = 'O';
			init(N * i + j, cnt + 1);
			map[i][j] = 'X';
		}
	}
}
int main(void) {
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	init(0, 0);

	ans ? (cout << "YES\n") : (cout << "NO\n");

	return 0;
}
