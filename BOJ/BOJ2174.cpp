/*
  단순 시뮬레이션
  
	로봇 좌표 (x, y) 의 x는 가로 y는 세로를 의미
	N : y 증가
	E : x 증가
	S : y 감소
	W : x 감소
*/
#include<iostream>

using namespace std;

struct info {
	int x, y, d;
};

int A, B, N, M;
int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };
info robot[101];

bool isInside(int x, int y) {
	return (1 <= x && x <= A && 1 <= y && y <= B);
}

int isCrashed(int x, int y, int i) {
	for (int j = 1; j <= N; j++) {
		if (i == j) continue;
		if (robot[j].x == x && robot[j].y == y) return j;
	}
	return 0;
}

int changeDir(char d) {
	if (d == 'N') return 0;
	else if (d == 'E') return 1;
	else if (d == 'S') return 2;
	else return 3;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> A >> B >> N >> M;

	int x, y;
	char d;
	for (int i = 1; i <= N; i++) {
		cin >> x >> y >> d;
		robot[i] = { x, y, changeDir(d) };
	}

	bool finish = true;
	for (int i = 1, ind, cnt; i <= M; i++) {
		cin >> ind >> d >> cnt; // x번 로봇을 d에 대해서 y번 반복
		if (d == 'F') {
			while (cnt--) {
				robot[ind].x = (robot[ind].x + dx[robot[ind].d]);
				robot[ind].y = (robot[ind].y + dy[robot[ind].d]);
				if (!isInside(robot[ind].x, robot[ind].y)) {
					cout << "Robot " << ind << " crashes into the wall\n";
					finish = false;
					i = M;
					break;
				}
				if (isCrashed(robot[ind].x, robot[ind].y, ind)) {
					cout << "Robot " << ind << " crashes into robot " << isCrashed(robot[ind].x, robot[ind].y, ind) << '\n';
					finish = false;
					i = M;
					break;
				}
			}
		}
		else if (d == 'L') {
			cnt %= 4;
			while (cnt--) {
				robot[ind].d = (robot[ind].d + 3) % 4;
			}
		}
		else if (d == 'R') {
			cnt %= 4;
			while (cnt--) {
				robot[ind].d = (robot[ind].d + 1) % 4;
			}
		}
	}
	if (finish) cout << "OK\n";

	return 0;
}
