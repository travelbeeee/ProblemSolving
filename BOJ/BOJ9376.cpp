/*
	BFS탐색 DP

	Map을 탈출해야되므로 입력된 Map 테두리에 '.' 를 셋팅해준다.

	각각 다른 시작 포인트에서 BFS탐색을 진행하며 (i, j)까지 
	문(#)을 최소한으로 부수며 이동할 때 문을 부순 횟수를 저장한다.
	
	1) Map 밖을 의미하는 (0, 0) 에서 시작한다 --> Map을 탈출한 경로를 의미
	2) 죄수1 에서 시작한다.
	3) 죄수2 에서 시작한다.

	--> breakDoor[i][j][0] + breakDoor[i][j][1] + breakDoor[i][j][2] 는
	(i, j) 까지 죄수1 과 죄수2가 문을 최소한으로 부수며 이동하고, 밖에서 문을 최소한으로 부수며 이동한 값으로
	우리가 원하는 값이 된다.

	이때, (i, j)가 문(#) 이라면 count가 2개 더 중첩된것이므로 
	breakDoor[i][j][0] + breakDoor[i][j][1] + breakDoor[i][j][2] - 2 가 원하는 값이 된다.

	모든 (i, j)를 순회하며 값이 가장 작아지는 지점을 찾는다.
*/

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int T, r, c;
int breakDoor[102][102][3];
vector<pair<int, int>> startP;
char map[102][102];

const int INF = 999999;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

bool isInside(int x, int y) {
	return (0 <= x && x <= r + 1 && 0 <= y && y <= c + 1);
}

void set(void) {
	startP.clear();
	for (int i = 0; i <= r + 1; i++)
		for (int j = 0; j <= c + 1; j++)
			for(int k = 0; k < 3; k++)
				breakDoor[i][j][k] = INF;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> T;
	while (T--) {
		cin >> r >> c;
		
		set();

		startP.push_back({ 0, 0 });
		for (int i = 0; i <= r + 1; i++){
			for (int j = 0; j <= c + 1; j++){
				if (i == 0 || i == r + 1 || j == 0 || j == c + 1)
					map[i][j] = '.';
				else 
					cin >> map[i][j];
				if (map[i][j] == '$') {
					startP.push_back({ i, j });
					map[i][j] = '.';
				}
			}
		}

		for (int i = 0; i < startP.size(); i++) {
			queue<pair<pair<int, int>, int>> q;
			q.push({{ startP[i].first, startP[i].second }, 0});
			breakDoor[startP[i].first][startP[i].second][i] = 0;

			while (!q.empty()) {
				pair<int, int> cur = q.front().first;
				int curL = q.front().second;
				q.pop();

				if (breakDoor[cur.first][cur.second][i] < curL) 
					continue;

				for (int j = 0; j < 4; j++) {
					int nextX = cur.first + dx[j], nextY = cur.second + dy[j];

					if (!isInside(nextX, nextY)) continue;
					if (map[nextX][nextY] == '*') continue;

					if (map[nextX][nextY] == '#') {
						if (curL + 1 < breakDoor[nextX][nextY][i]) {
							breakDoor[nextX][nextY][i] = curL + 1;
							q.push({ { nextX, nextY }, curL + 1 });
						}
					}
					else {
						if (curL < breakDoor[nextX][nextY][i]){
							breakDoor[nextX][nextY][i] = curL;
							q.push({ { nextX, nextY }, curL });
						}
					}
				}
			}
		}

		int ans = INF;

		for (int i = 0; i <= r + 1; i++)
			for (int j = 0; j <= c + 1; j++) {
				if (map[i][j] == '*') continue;
				int k = breakDoor[i][j][0] + breakDoor[i][j][1] + breakDoor[i][j][2];
				if (map[i][j] == '#') k -= 2;
				ans = min(ans, k);
			}

		cout << ans << '\n';
	}

	return 0;
}
