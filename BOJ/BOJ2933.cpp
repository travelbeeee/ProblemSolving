/*
	BFS 시뮬레이션

	1) breakMineral 함수 
	막대기를 던져서 미네랄을 부신다

	2) checkMineral 함수
	--> 2-1) 바닥에 'x'(미네랄)이 있는 부분에서 BFS 탐색을 진행
	--> 2-2) 그 결과가 현재 mineral 개수와 똑같다면 떨어지는 클러스터 X
	--> 2-3) 다르다면 2-1) 에서 탐색하지못한 'x'(미네랄) 들은 다 떨어져야됨
	--> 2-4) 탐색하지못한 미네랄들을 순회하면서 각 열마다 가장 밑바닥을 구함
	--> 2-5) 가장 밑바닥마다 얼마나 아래로 떨어질 수 있는지 구하고 
		그 중 가장 작은 값이 공중에 떠있는 클러스터가 떨어져야되는 크기
	--> 2-6) 2-5)에서 구한 값만큼 전체적으로 클러스터를 떨어뜨린다.

*/
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int R, C, N, mineral;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
char map[100][101];

bool isInside(pair<int, int> c) {
	return (0 <= c.first && c.first < R && 0 <= c.second && c.second < C);
}

void breakMineral(int h, bool flag) {
	int sy[2] = { 0, C - 1 }, ey[2] = { C , -1 }, dy[2] = { 1, -1 };
	int j = sy[flag];
	do {
		if (map[h][j] == 'x') {
			map[h][j] = '.'; 
			mineral--;
			break;
		}
		j += dy[flag];
	} while (j != ey[flag]);

	return;
}

void checkMineral(void) {
	int cnt = 0;
	bool visited[100][100] = {};
	// 바닥에 붙어있는 미네랄에서 BFS탐색진행
	for (int j = 0; j < C; j++) {
		if (map[0][j] == 'x' && !visited[0][j]) { 
			queue<pair<int, int>> q;
			q.push({ 0, j });
			cnt++;
			visited[0][j] = 1;

			while (!q.empty()) {
				pair<int, int> cur = q.front();
				q.pop();

				for (int k = 0; k < 4; k++) {
					pair<int, int> next = { cur.first + dx[k], cur.second + dy[k] };
					if (!isInside(next)) continue;
					if (visited[next.first][next.second]) continue;
					if (map[next.first][next.second] != 'x') continue;

					visited[next.first][next.second] = true;
					cnt++;
					q.push(next);
				}
			}
		}
	}
	// 바닥에 다 붙어있는 경우 --> 끝낸다.
	if (cnt == mineral) return;

	// 아닌 경우는 visited로 체크되지않은 떨어져야하는클러스터를 찾자!
	bool droped[100][100] = {};
	int floor[100] = {};
	for (int j = 0; j < C; j++)
		floor[j] = 101;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == 'x' && !visited[i][j]) {
				// 떨어져야하는클러스터를 순회하며 각 열에서 가장 밑바닥을 찾자
				queue<pair<int, int>> q;
				q.push({ i, j });
				droped[i][j] = 1;
				floor[j] = min(floor[j], i);
				while (!q.empty()) {
					pair<int, int> cur = q.front();
					q.pop();

					for (int k = 0; k < 4; k++) {
						pair<int, int> next = { cur.first + dx[k], cur.second + dy[k] };
						if (!isInside(next)) continue;
						if (droped[next.first][next.second]) continue;
						if (map[next.first][next.second] != 'x') continue;
						floor[next.second] = min(floor[next.second], next.first);
						droped[next.first][next.second] = true;
						q.push({ next });
					}
				}
				i = R, j = C;
			}
		}
	}
	// 밑바닥마다 얼마나 떨어질 수 있는지 체크하고 가장 작은 값만큼 내린다.
	int downSize = 101;
	for (int j = 0; j < C; j++) {
		if (floor[j] == 101) continue;
		int r = floor[j] - 1, downCnt = 0;
		// (flood[j], j) 부터 내려가면서 '.' 까지
		while (0 <= r && map[r][j] == '.') {
			r--;
			downCnt++;
		}
		downSize = min(downSize, downCnt);
	}
	// downSize 만큼씩 다 내리자
	for (int i = 0; i < R; i++)
		for(int j = 0; j < C; j++)
			if (droped[i][j]) {
				map[i - downSize][j] = 'x';
				map[i][j] = '.';
			}
	return;
}

void printMap() {
	for (int i = R - 1; i >= 0; i--)
		cout << map[i] << '\n';
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> R >> C;
	for (int i = R - 1; i >= 0; i--)
		cin >> map[i];

	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (map[i][j] == 'x') mineral++;

	cin >> N;
	for (int i = 0, x; i < N; i++) {
		cin >> x;
		x--;
		breakMineral(x, i % 2);
		checkMineral();
	}
	printMap();

	return 0;
}
