/*
	단순 구현
	입력으로 들어오는 값의 행, 열만 헷갈리지말고 잘 처리하면 된다.
*/
#include<iostream>

using namespace std;

int N, kingX, kingY, rockX, rockY, nextKX, nextKY, nextRX, nextRY;
int dx[26][26], dy[26][26];
string dir, king, rock;

bool isInside(int x, int y) {
	return (0 <= x && x < 8 && 0 <= y && y < 8);
}

void set(void) {
	kingY = king[0] - 'A';
	kingX = king[1] - '1';
	rockY = rock[0] - 'A';
	rockX = rock[1] - '1';

	dy['R' - 'A'][0] = 1;
	dy['L' - 'A'][0] = -1;
	dx['B' - 'A'][0] = -1;
	dx['T' - 'A'][0] = 1;

	dx['R' - 'A']['T' - 'A'] = 1;
	dy['R' - 'A']['T' - 'A'] = 1;

	dx['L' - 'A']['T' - 'A'] = 1;
	dy['L' - 'A']['T' - 'A'] = -1;

	dx['R' - 'A']['B' - 'A'] = -1;
	dy['R' - 'A']['B' - 'A'] = 1;

	dx['L' - 'A']['B' - 'A'] = -1;
	dy['L' - 'A']['B' - 'A'] = -1;
}

void move(string d) {
	int firstD = d[0] - 'A', secondD = 0;
	if (d.size() == 2) secondD = d[1] - 'A';
	
	nextKX = kingX + dx[firstD][secondD];
	nextKY = kingY + dy[firstD][secondD];
	
	if (!isInside(nextKX, nextKY)) return;

	if (nextKX == rockX && nextKY == rockY) {
		nextRX = rockX + dx[firstD][secondD];
		nextRY = rockY + dy[firstD][secondD];
		if (!isInside(nextRX, nextRY)) return;

		kingX = nextKX, kingY = nextKY;
		rockX = nextRX, rockY = nextRY;
	}
	else {
		kingX = nextKX, kingY = nextKY;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> king >> rock >> N;

	set();

	for (int i = 0; i < N; i++) {
		cin >> dir;
		move(dir);
	}
	cout << char(kingY + 'A') << kingX + 1 << '\n';
	cout << char(rockY + 'A') << rockX + 1<< '\n';

	return 0;
}
