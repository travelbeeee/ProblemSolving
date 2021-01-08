/*
	BFS탐색

	BFS탐색을 통해 (0, 0) --> (N - 1, N - 1)까지 탐색 진행.

	그럼 visited배열을 어떻게 설정해야될까.
	우리에게 필요한 정보는 현재 내가 (i, j) 지점에 있고, 여기까지 오는데 (최솟값, 최댓값)
	총 4가지 정보에 따라 이전에 방문했는지 안했는지 판단 할 수 있다.
	또, (i, j) 지점에 같은 최솟값으로 도착했는데 
	기존에 탐색을 진행한 사례보다 최댓값이 더 큰 경우는
	정답 조건에 부합하지 않으므로 탐색을 진행하지 않는다.

	--> visited[x좌표][y좌표][최솟값] = 최댓값
*/

#include<iostream>
#include<queue>
#include<algorithm>
#include<cmath>

using namespace std;

int N, map[100][100], ans = 200;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
int visited[100][100][201] = {};
queue<pair<pair<int, int>, pair<int, int>>> q;

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < N);
}

void set(void) {
	while (!q.empty()) q.pop();

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k <= 200; k++)
				visited[i][j][k] = 201;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	set();
	q.push({ {0, 0},  {map[0][0], map[0][0]} });
	visited[0][0][map[0][0]] = map[0][0];

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int curMin = q.front().second.first;
		int curMax = q.front().second.second;

		q.pop();

		if (cur.first == N - 1 && cur.second == N - 1) {
			ans = min(ans, curMax - curMin);
			continue;
		}

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;

			int nextMin = min(curMin, map[nextX][nextY]);
			int nextMax = max(curMax, map[nextX][nextY]);

			if (visited[nextX][nextY][nextMin] <= nextMax) continue;

			visited[nextX][nextY][nextMin] = nextMax;
			q.push({ {nextX, nextY}, {nextMin, nextMax} });
		}
	}

	cout << ans << '\n';

	return 0;
}