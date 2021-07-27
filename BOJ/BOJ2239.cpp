/*
	백트레킹
*/
#include<iostream>

using namespace std;

string map[9];
bool isFinish;

void Backtracking(int x, int y) {
	if (isFinish) return;

	if (x == 9) {
		for (int i = 0; i < 9; i++)
			cout << map[i] << '\n';
		isFinish = true;
		return;
	}

	if (map[x][y] != '0') {
		if (y + 1 == 9)
			Backtracking(x + 1, 0);
		else
			Backtracking(x, y + 1);
	}
	else { // map[x][y] 에 들어갈 수 있는 숫자들을 다 넣어보자.
		bool isCanTNum[10] = {};
		for (int j = 0; j < 9; j++)
			isCanTNum[map[x][j] - '0'] = true;
		for (int i = 0; i < 9; i++)
			isCanTNum[map[i][y] - '0'] = true;
		int boxX = x / 3;
		int boxY = y / 3;
		// (3 * boxX, 3 * boxY) 에서 길이가 3인 정사각형을 그려서 탐색
		for (int i = 3 * boxX; i < 3 * boxX + 3; i++) {
			for (int j = 3 * boxY; j < 3 * boxY + 3; j++) {
				isCanTNum[map[i][j] - '0'] = true;
			}
		}
		for (int i = 1; i < 10; i++) {
			if (!isCanTNum[i]) {
				map[x][y] = '0' + i;
				if (y + 1 == 9)
					Backtracking(x + 1, 0);
				else
					Backtracking(x, y + 1);
				map[x][y] = '0';
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	for (int i = 0; i < 9; i++)
		cin >> map[i];

	Backtracking(0, 0);

	return 0;
}
