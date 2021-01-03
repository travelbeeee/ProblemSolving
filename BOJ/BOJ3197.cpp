/*
	BFS탐색

	1) 먼저 각 'X'(얼음) 마다 녹는 시간을 구한다.
	- 테두리가 되는 'X'(얼음)을 checkCover 함수를 이용해 찾은 다음에
	  테두리 얼음부터 BFS 탐색을 진행해나가며 모든 'X'(얼음) 마다 녹는 시간을 구한다.

	2) 백조에서 다른 백조로 이동을 하는데 우리는 이동경로에 있는 얼음 녹는 시간의 최대값이 제일 작은 값을 원함.
	--> 탐색을 진행해나가며 지나쳐온 경로의 1) 에서 구한 얼음 녹는 시간의 최대값을 저장해나간다.
	--> 그 값이 제일 작은 경로가 우리가 원하는 답!
  
*/
#include<iostream>
#include<queue>

using namespace std;

int r, c;
int meltingTime[1500][1500];
int ans[1500][1500];
char map[1500][1501];

int sX, sY, eX, eY;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1 , 0, 1 };

queue<pair<int, int>> q;

bool isInside(int x, int y) {
	return (0 <= x && x < r && 0 <= y && y < c);
}

bool checkCover(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nX = x + dx[i], nY = y + dy[i];
		if (!isInside(nX, nY)) continue;
		if (map[nX][nY] == '.') return true;
	}
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> r >> c;
	for (int i = 0; i < r; i++)
		cin >> map[i];

	for (int i = 0; i < r; i++)
		for(int j = 0; j < c; j++)
			if (map[i][j] == 'L') {
				sX = i, sY = j, map[i][j] = '.';
				i = r, j = c;
			}
	for (int i = 0; i < r; i++)
		for(int j = 0; j < c; j++)
			if (map[i][j] == 'L') {
				eX = i, eY = j, map[i][j] = '.';
				i = r, j = c;
			}

	// 각 얼음마다 녹는 시간을 구해보자.
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			if (map[i][j] == 'X' && checkCover(i, j)){
				q.push({ i, j });
				meltingTime[i][j] = 1;
			}

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (map[nextX][nextY] != 'X') continue;
			if (meltingTime[nextX][nextY]) continue;

			meltingTime[nextX][nextY] = meltingTime[cur.first][cur.second] + 1;
			q.push({ nextX, nextY });
		}
	}

	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			ans[i][j] = 1500 * 1500;
	ans[sX][sY] = 0;
	q.push({ sX, sY });
	
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		//cout << cur.first << ' ' << cur.second << ' ' << ans[cur.first][cur.second] << "로탐방중\n";
		if (cur.first == eX && cur.second == eY)
			continue;

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (ans[nextX][nextY] <= max(ans[cur.first][cur.second], meltingTime[nextX][nextY])) continue;

			ans[nextX][nextY] = max(meltingTime[nextX][nextY], ans[cur.first][cur.second]);
			q.push({ nextX, nextY });
		}
	}

	cout << ans[eX][eY] << '\n';

	return 0;
}
