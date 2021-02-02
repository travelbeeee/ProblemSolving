/*
	2차원 DP

	Dp[i][j] := 0번 체크포인트부터 j번 체크포인트까지 이동하는데 i번 스킵한 최소!

*/
#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;

const int INF = 99999999;
int N, K, dp[500][500];
pair<int, int> points[500];

int getDist(int i, int j) {
	return (abs(points[i].first - points[j].first) + abs(points[i].second - points[j].second));
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> points[i].first >> points[i].second;
	
	// 0번 N - 1번 포인트는 무조건 지나가야되므로! 어차피 최대(N - 2)개 밖에 못지움
	if (N - 1 == K)
		K--;
	for (int i = 0; i <= K; i++)
		for (int j = 0; j < N; j++)
			dp[i][j] = INF;

	dp[0][0] = 0;
	for (int j = 1; j < N; j++)
		dp[0][j] = dp[0][j - 1] + getDist(j, j - 1);

	for (int i = 1; i <= K; i++)
		for (int j = i + 1; j < N; j++) 
			for (int k = 0; k <= i; k++)
				dp[i][j] = min(dp[i][j], dp[k][(j - i) - 1 + k] + getDist((j - i) - 1 + k, j));
	

	cout << dp[K][N - 1] << '\n';

	return 0;
}
