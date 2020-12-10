/*
  1) 모래날리기
   모래 날리는 값에 대해서 방향별로 moveX, moveY 를 미리 셋팅해놓으면 구현은 간단하다.
  2) Map 이동
   처음엔 크기 1씩 2번 이동, 크기 2씩 2번 이동 ....
   이런 식으로 2번 이동을 마치면 이동해야하는 크기가 커진다.
   하지만, 마지막 이동 때는 같은 크기로 3번 이동을 해야되므로 이때만 따로 처리해주면 된다.
   
*/ 
#include<iostream>

using namespace std;

int N, map[499][499], mov = 1, cnt, ans, siz = 1;
int sX, sY, nX, nY, dir;
int dx[4] = { 0, 1, 0, -1 }, dy[4] = { -1, 0, 1, 0 };
int moveX[4][9] = {
	{ -2, -1, -1, -1, 0, 1, 1, 1, 2 },
	{1, 2, 1, 0, 3, 2, 1, 0, 1},
	{2, 1, 1, 1, 0, -1, -1, -1, -2},
	{-1, -2, -1, 0, -3, -2, -1, 0, -1}
};
int moveY[4][9] = {
	{ -1, -2, -1, 0, -3, -2, -1, 0, -1 },
	{ -2, -1, -1, -1, 0, 1, 1, 1, 2},
	{1, 2, 1, 0, 3, 2, 1, 0, 1},
	{-2, -1, -1, -1, 0, 1, 1, 1, 2}
};
int moveS[9] = { 2, 10, 7, 1, 5, 10, 7, 1, 2 };

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < N);
}

void moveSand(void) {
	// sX, sY에서 nX nY로 이동!
	int movedSand = 0;
	// (nX nY) 의 모래들을 비율에 따라 날린다
	for (int i = 0; i < 9; i++) {
		int nextX = sX + moveX[dir][i], nextY = sY + moveY[dir][i], nextS = (map[nX][nY] * moveS[i]) / 100;
		movedSand += nextS;
		if (!isInside(nextX, nextY)) ans += nextS;
		else map[nextX][nextY] += nextS;
	}
	// 남은 (nX nY) 모래들을 a에 날린다
	if (!isInside(nX + dx[dir], nY + dy[dir])) ans += (map[nX][nY] - movedSand);
	else map[nX + dx[dir]][nY + dy[dir]] += (map[nX][nY] - movedSand);

	map[nX][nY] = 0;
	return;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	
	sX = (N / 2), sY = (N / 2);

	while (siz <= N - 1) {
		// siz 만큼 이동!
		for (int i = 0; i < siz; i++) {
			nX = sX + dx[dir], nY = sY + dy[dir];
			moveSand();
			sX = nX, sY = nY;
		}
		dir = (dir + 1) % 4, cnt++;
		if (siz == N - 1) {
			if (cnt == 3) siz++;
		}
		else if (cnt == 2) {
			cnt = 0, siz++;
		}
		mov++;
	}

	cout << ans << '\n';

	return 0;
}
