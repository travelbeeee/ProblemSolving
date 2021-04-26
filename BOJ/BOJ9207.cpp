/*
  단순 완전탐색 구현...!
*/
#include<iostream>
#include<algorithm>

using namespace std;

const int INF = 99999999;
const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
int t, minPen, minJump;

bool isInside(int x, int y) {
	return (0 <= x && x < 5 && 0 <= y && y < 9);
}

void DFS(int jump, string map[5]) {
	// 답 갱신!
	int penCnt = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 9; j++)
			if (map[i][j] == 'o') penCnt++;


	if (penCnt < minPen) {
		minPen = penCnt;
		minJump = jump;
	}
	else if (penCnt == minPen) {
		minJump = min(minJump, jump);
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			if (map[i][j] != 'o') continue;
			for (int dir = 0; dir < 4; dir++) {
				int nextPinX = i + dx[dir], nextPinY = j + dy[dir];
				int nextHoleX = i + 2 * dx[dir], nextHoleY = j + 2 * dy[dir];
				if (!isInside(nextPinX, nextPinY) || !isInside(nextHoleX, nextHoleY)) continue;
				if (map[nextPinX][nextPinY] == 'o' && map[nextHoleX][nextHoleY] == '.') {
					map[i][j] = '.';
					map[nextPinX][nextPinY] = '.';
					map[nextHoleX][nextHoleY] = 'o';

					DFS(jump + 1, map);

					map[nextHoleX][nextHoleY] = '.';
					map[nextPinX][nextPinY] = 'o';
					map[i][j] = 'o';
				}
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> t;
	while (t--) {
		string map[5], CRLF;
		for (int i = 0; i < 5; i++)
			cin >> map[i];

		minPen = minJump = INF;
		
		DFS(0, map);

		cout << minPen << ' ' << minJump << '\n';
	}
	return 0;
}
