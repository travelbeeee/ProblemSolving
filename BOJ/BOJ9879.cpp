/*
	인접한 지역끼리의 이동은 어떤 기준(D) 이하의 차이가 날 때에만 가능하고
	wayPoint로 체크된 지역끼리 서로 이동이 
	이때, 가장 작은 D 값은 무엇인가??

	--> BFS탐색 && Binary Search로 해결 가능
*/
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

int N, M, ans, l, r;
int map[500][500];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
vector<pair<int, int>> wayPoint;

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < M);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++){
			cin >> map[i][j];
			r = max(r, map[i][j]);
		}

	for (int i = 0; i < N; i++)
		for (int j = 0, x; j < M; j++) {
			cin >> x;
			if (x) wayPoint.push_back({ i, j });
		}

	ans = r;
	while (l <= r) {
		int m = (l + r) / 2;
		// m 를 D 삼아 BFS 탐색 진행
		queue<pair<int, int>> q;
		bool visited[500][500] = {};

		q.push({ wayPoint[0] });
		visited[wayPoint[0].first][wayPoint[0].second];

		while (!q.empty()) {
			pair<int, int> cur = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
				if (!isInside(nextX, nextY)) continue;
				if (visited[nextX][nextY]) continue;
				if (abs(map[cur.first][cur.second] - map[nextX][nextY]) > m) continue;

				visited[nextX][nextY] = true;
				q.push({ nextX, nextY });
			}
		}
		bool check = true;
		for (int i = 0; i < wayPoint.size(); i++) {
			if (!visited[wayPoint[i].first][wayPoint[i].second]) {
				check = false;
				break;
			}
		}
		if (check) {
			r = m - 1;
			ans = min(ans, m);
		}
		else {
			l = m + 1;
		}
	}
	cout << ans << '\n';

	return 0;
}
