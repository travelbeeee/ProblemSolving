/*
	DP

	DP[i][j] := (i, j)에서 시작해서 왼쪽 위 (0, 0)쪽으로 
				그릴 수 있는 가장 큰 정사각형 길이

	--> DP[i][j] 는 map[i - 1][j - 1], map[i][j - 1], map[i - 1][j] 
		가 지을 수 있는 곳이라면 3개의 DP값 중 가장 작은 값에 +1을 해서 목장을 지을 수 있다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

int N, M;
int map[1000][1000];
int dp[1000][1000];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	// 기본 DP셋팅
	for (int i = 0; i < N; i++)
		if (map[i][0] == 0) dp[i][0] = 1;
	for (int j = 0; j < M; j++)
		if (map[0][j] == 0) dp[0][j] = 1;

	for (int i = 1; i < N; i++) {
		for (int j = 1; j < M; j++) {
			if (map[i][j] != 0) continue;
			if (dp[i - 1][j - 1] && dp[i][j - 1] && dp[i - 1][j])
				dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
			else
				dp[i][j] = 1;
		}
	}

	int ans = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			ans = max(ans, dp[i][j]);
	cout << ans << '\n';

	return 0;
}
