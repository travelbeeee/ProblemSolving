#include<iostream>

using namespace std;

int r, c, t;
int dx[26], dy[26];
string map[15], orders;

void setDir(void) {
	dx['U' - 'A'] = -1; dx['D' - 'A'] = 1;
	dx['L' - 'A'] = 0; dx['R' - 'A'] = 0;
	dy['U' - 'A'] = 0; dy['D' - 'A'] = 0;
	dy['L' - 'A'] = -1; dy['R' - 'A'] = 1;
}

bool isInside(int x, int y) {
	return (0 <= x && x < r && 0 <= y && y < c);
}

bool isFinishGame(void) {
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			if (map[i][j] == 'b') return false;
	return true;
}

void printMap(void) {
	for (int i = 0; i < r; i++)
		cout << map[i] << '\n';
}

bool doGame(int curX, int curY, string orders) {
	for (char order : orders) {
		int nextX = curX + dx[order - 'A'], nextY = curY + dy[order - 'A'];
		if (!isInside(nextX, nextY)) continue;
		if (map[nextX][nextY] == '#') continue;

		// 박스를 밀어야한다.
		if (map[nextX][nextY] == 'b' || map[nextX][nextY] == 'B') {
			int boxX = nextX + dx[order - 'A'], boxY = nextY + dy[order - 'A'];
			if (!isInside(boxX, boxY)) continue;
			if (map[boxX][boxY] == '#' || map[boxX][boxY] == 'b' || map[boxX][boxY] == 'B') continue;

			// 박스이동
			if (map[boxX][boxY] == '+') map[boxX][boxY] = 'B';
			else map[boxX][boxY] = 'b';
			// 원래박스있던자리셋팅
			if (map[nextX][nextY] == 'B') map[nextX][nextY] = '+';
			else map[nextX][nextY] = '.';
		}

		// 사람이동
		if (map[nextX][nextY] == '+') map[nextX][nextY] = 'W';
		else map[nextX][nextY] = 'w';
		// 원래사람잇던자리셋팅
		if (map[curX][curY] == 'W') map[curX][curY] = '+';
		else map[curX][curY] = '.';

		curX = nextX, curY = nextY;
		if (isFinishGame()) return true;
	}
	return false;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	setDir();


	while (1) {
		cin >> r >> c;
		if (r == 0 && c == 0) break;

		for (int i = 0; i < r; i++)
			cin >> map[i];

		cin >> orders;

		int curX, curY;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				if (map[i][j] == 'w' || map[i][j] == 'W')
					curX = i, curY = j;

		cout << "Game " << ++t << ": ";
		doGame(curX, curY, orders) ? (cout << "complete\n") : (cout << "incomplete\n");
		printMap();
	}

	return 0;
}
