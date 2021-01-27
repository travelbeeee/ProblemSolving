/*
	BFS탐색

	어떤 지점 [i][j] 에 물 k 를 채우려면 그 지점이 k보다 높거나 같은
	벽으로 둘러싸인 지점이여야 된다.
	--> 땅 밖에서 탐색을 시작해 k보다 작은 값들만 탐색을 진행하자.
	--> 탐색을 진행하고 [i][j] 를 방문할 수 없었다면 k보다 높거나 같은 벽으로 둘러싸인 지점이다!
	--> [i][j] 에 물을 k까지 채울 수 있다!

	물을 최소 2 ~ 9 까지 채울 수 있으므로 각 물의 높이별로 땅 밖의 범위에서 탐색을 시작해
	[i][j] 지점마다 최대로 채울 수 있는 물의 높이를 구하면 된다.

*/
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int N, M;
int walls[52][52];
int res[52][52];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
bool visited[52][52];
string map[50];

void set(void) {
	for (int i = 0; i <= N + 1; i++)
		for (int j = 0; j <= M + 1; j++)
			visited[i][j] = false;
}

bool isInside(int x, int y) {
	return (0 <= x && x <= N + 1 && 0 <= y && y <= M + 1);
}

void BFS(int water) {
	queue<pair<int, int>> q;
	q.push({ 0, 0 });
	visited[0][0] = true;

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (visited[nextX][nextY]) continue;
			if (water <= walls[nextX][nextY]) continue;
			visited[nextX][nextY] = true;
			q.push({ nextX, nextY });
		}
	}

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (!visited[i][j] && water - walls[i][j] > 0)
				res[i][j] = water - walls[i][j];
}

int getAns() {
	int ans = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			ans += res[i][j];
	return ans;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> map[i];

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			walls[i][j] = map[i - 1][j - 1] - '0';

	for (int water = 2; water <= 9; water++) {
		set();
		BFS(water);
	}
	
	cout << getAns() << '\n';

	return 0;
}
