/*
  
*/
#include<iostream>

using namespace std;

const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
int N, M, R, score = 0;
int domino[101][101];
bool isFall[101][101] = {};

bool isInside(int x, int y) {
	return (1 <= x && x <= N && 1 <= y && y <= M);
}

void fallDomino(int x, int y, char dir) {
	if (isFall[x][y]) return;

	int d;
	if (dir == 'N') d = 0;
	else if (dir == 'W') d = 1;
	else if (dir == 'S') d = 2;
	else d = 3;

	int len = domino[x][y] - 1;
	isFall[x][y] = true;
	score++;

	while (len) {
		x += dx[d], y += dy[d];
		if (!isInside(x, y)) break;
		if (isFall[x][y]) len--;
		else {
			len = max(len - 1, domino[x][y] - 1);
			score++;
		}
		isFall[x][y] = true;
	}

	return;
}

void printStatus() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << isFall[i][j] << ' ';
		}
		cout << '\n';
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);


	cin >> N >> M >> R;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> domino[i][j];

	int x, y;
	char dir;
	for (int i = 0; i < R; i++) {
		cin >> x >> y >> dir;
		fallDomino(x, y, dir);
		cin >> x >> y;
		isFall[x][y] = false;
	}

	cout << score << '\n';
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (isFall[i][j]) cout << "F ";
			else cout << "S ";
		}
		cout << '\n';
	}
}
