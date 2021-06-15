#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	const int dx[4] = { -1, 0, 1, 0 };
	const int dy[4] = { 0, -1, 0, 1 };

	int N, M, K;
	bool map[101][101] = {};

	cin >> N >> M >> K;
	for (int i = 0, r, c; i < K; i++) {
		cin >> r >> c;
		map[r][c] = true;
	}

	int maxArea = 0;
	bool visited[101][101] = {};
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (!visited[i][j] && map[i][j]) {
				queue<pair<int, int>> q;
				int area = 1;

				q.push({ i, j });
				visited[i][j] = true;
				while (!q.empty()) {
					pair<int, int> cur = q.front();
					q.pop();

					for (int k = 0; k < 4; k++) {
						int nextX = cur.first + dx[k], nextY = cur.second + dy[k];
						if (!(1 <= nextX && nextX <= N && 1 <= nextY && nextY <= M)) continue;
						if (visited[nextX][nextY]) continue;
						if (!map[nextX][nextY]) continue;

						q.push({ nextX, nextY });
						visited[nextX][nextY] = true;
						area++;
					}
				}

				maxArea = max(maxArea, area);
			}
		}
	}
	cout << maxArea << '\n';

	return 0;
}
