/*
  1) Catan Board 의 6 방향의 인접한 Board를 다음과 같이 2차원 배열을 통해 표현했다.
  
                    (x - 2, y)
    (x - 1, y - 1)              (x - 1, y + 1)
                      (x, y)
    (x + 1, y - 1)              (x + 1, y + 1)
                    (x + 2, y)
                    
    이러면 현재 위치에서 자원을 선택하는 경우는 6가지 방향에 있는 자원들을 체크하고,
    없는 자원 중에 가장 적은 값을 선택하면 된다. ( sumResource[i] := i 자원이 몇 번 등장했는지 )
    
  2) Catan Board를 채울 때 6 방향 중 위로 향하는 방향은 다른 방향에 비해 1번 씩 적게 나타난다
  --> 다음과 같이 위로 향하는 방향이 나오는 경우에는 현재 몇 번 그 방향으로 이동했는지 cnt를 + 1 해서 계산한다.
		if (dir == 1 && cnt + 1 == level) {
			cnt = 0;
			dir = (dir + 1) % 6;
			if (dir == 0) level++;
		}
*/
#include<iostream>
#include<algorithm>

using namespace std;

int sumResource[6];
int board[1001][1001];
pair<int, int> position[10001];
int dx[6] = { -1, -2, -1, 1, 2, 1 }, dy[6] = { 1, 0, -1, -1, 0, 1 };

int choiceResource(int x, int y) {
	// 이미 선택된 자원들은 배제!
	bool isCant[6] = {};
	for (int i = 0; i < 6; i++) {
		int nextX = x + dx[i], nextY = y + dy[i];
		isCant[board[nextX][nextY]] = true;
	}
	int m = 99999;
	for (int i = 1; i <= 5; i++) {
		if (!isCant[i]) m = min(m, sumResource[i]);
	}
	for (int i = 1; i <= 5; i++)
		if (!isCant[i] && sumResource[i] == m)
			return i;
}

void setBoard(void) {
	int i = 1, sX = 500, sY = 500, cnt = 0, dir = 0, level = 1;
	while (i <= 10000) {
		if (dir != 1 && cnt == level) {
			cnt = 0;
			dir = (dir + 1) % 6;
			if (dir == 0) level++;
		}
		if (dir == 1 && cnt + 1 == level) {
			cnt = 0;
			dir = (dir + 1) % 6;
			if (dir == 0) level++;
		}

		position[i] = { sX, sY };
		board[sX][sY] = choiceResource(sX, sY);
		sumResource[board[sX][sY]]++;

		sX += dx[dir], sY += dy[dir];
		cnt++, i++;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	setBoard();

	int c, n;
	cin >> c;
	while (c--) {
		cin >> n;
		cout << board[position[n].first][position[n].second] << '\n';
	}
}
