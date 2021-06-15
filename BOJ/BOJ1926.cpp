#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, -1, 0, 1 };

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, M;
	bool map[500][500] = {};

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	int maxArea = 0, picN = 0;
	bool visited[500][500] = {};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] && !visited[i][j]) { // 아직 탐색 안한 그림
				queue<pair<int, int>> q;
				int area = 1;

				q.push({ i, j });
				visited[i][j] = 1;
				while (!q.empty()) {
					pair<int, int> cur = q.front();
					q.pop();

					for (int k = 0; k < 4; k++) {
						int nextX = cur.first + dx[k], nextY = cur.second + dy[k];
						if (!(0 <= nextX && nextX < N && 0 <= nextY && nextY < M)) continue;
						if (visited[nextX][nextY]) continue;
						if (!map[nextX][nextY]) continue;

						q.push({ nextX, nextY });
						visited[nextX][nextY] = true;
						area++;
					}
				}
				picN++;
				maxArea = max(maxArea, area);
			}
		}
	}
	cout << picN << '\n' << maxArea << '\n';

	return 0;
}
