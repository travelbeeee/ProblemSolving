#include<iostream>
#include<queue>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	// 위 오른쪽 아래 왼쪽
	const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };

	int t;
	cin >> t;
	while (t--) {
		int n, r, sX, sY;
		bool mirror[52][52] = {};
		bool visited[52][52][4] = {};

		cin >> n >> r;
		for (int i = 0, x, y; i < r; i++) {
			cin >> x >> y;
			mirror[x][y] = true;
		}
		cin >> sX >> sY;
		int dir = 0;
		if (sX == n + 1) dir = 0; //위
		else if (sX == 0) dir = 2; // 아래
		else if (sY == 0) dir = 1; //오른쪽
		else if (sY == n + 1) dir = 3; //왼쪽

		visited[sX][sY][dir] = true;
		while (1) {
			int nextX = sX + dx[dir], nextY = sY + dy[dir];

			if (mirror[nextX][nextY]) dir = (dir + 1) % 4;

			if (visited[nextX][nextY][dir]) {
				sX = 0, sY = 0;
				break;
			}

			sX = nextX, sY = nextY;
			visited[sX][sY][dir] = true;

			if (sX == 0 || sX == n + 1 || sY == 0 || sY == n + 1) break;
		}
		cout << sX << ' ' << sY << '\n';
	}
}
