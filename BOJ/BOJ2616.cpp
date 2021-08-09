/*
	DP

	Dp[i][k] := (k - 1)개의 미니 열차를 이용해서 1 ~ i 번 째 객차에서 얻을 수 있는 최대값.
*/
#include<iostream>
#include<algorithm>

using namespace std;

int N, K;
int train[50001];
int sum[50001]; // i번째 객차부터 K개를 가져옴 --> sum[i + (K - 1)] - sum[i - 1];
int dp[50001][3];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++){
		cin >> train[i];
		sum[i] = sum[i - 1] + train[i];
	}
	cin >> K;

	int ans = 0;
	for (int t = 0; t < 3; t++) {
		for (int c = K; c <= N; c++) {
			if (t == 0) // 첫 번째 열차만 사용
				dp[c][t] = max(dp[c - 1][t], sum[c] - sum[c - K]);
			else
				dp[c][t] = max(dp[c - 1][t], dp[c - K][t - 1] + sum[c] - sum[c - K]);
			ans = max(ans, dp[c][t]);
		}
	}
	cout << ans << '\n';
	return 0;
}
