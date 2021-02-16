/*
	BFS탐색 DP

	4방향으로 (0, 0) 에서 시작해서 탐색을 진행하면 된다.
	dp[i][j] := (i, j)에 최대로 움직여서 도착한 횟수
	--> dp[i][j] 가 N * M 보다 커지면 모든 칸을 밟고도 더 밟은거므로 
		중복발생!!
	--> loop 에 갇힌 상황이다.
*/
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int INF = 9999;
int N, M, dp[50][50], ans = -1;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
string map[50];

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < M);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> map[i];

	queue<pair<int, int>> q;
	q.push({ 0, 0 });
	dp[0][0] = 1;

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		if (dp[cur.first][cur.second] > N * M) continue;

		int jump = map[cur.first][cur.second] - '0';
		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + jump * dx[i], nextY = cur.second + jump * dy[i];
			if (!isInside(nextX, nextY) || map[nextX][nextY] == 'H') { // 게임종료
				ans = max(ans, dp[cur.first][cur.second]);
			}
			else if (dp[nextX][nextY] < dp[cur.first][cur.second] + 1){
				dp[nextX][nextY] = dp[cur.first][cur.second] + 1;
				ans = max(ans, dp[nextX][nextY]);
				q.push({ nextX, nextY });
			}
		}
	}

	if (ans > N * M) ans = -1;
	cout << ans << '\n';

	return 0;
}
