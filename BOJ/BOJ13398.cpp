/*
	동적프로그래밍

	dp[0][i] := (0 ~ i)번 째 까지 최대 연속합(i번 째 원소는 무조건 선택)
	dp[1][i] := (0 ~ i)번 째 까지 1개의 수를 삭제한 최대 연속합(i번 째 원소는 무조건 선택)
*/

#include<iostream>
#include<algorithm>

using namespace std;

int n, sequence[100000], dp[2][100000];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> sequence[i];

	dp[0][0] = dp[1][0] = sequence[0];
	for (int i = 1; i < n; i++) {
		dp[0][i] = max(dp[0][i - 1] + sequence[i], sequence[i]);
		dp[1][i] = max(max(dp[1][i - 1] + sequence[i], dp[0][i - 1]), sequence[i]);
	}

	int ans = -100000000;
	for (int i = 0; i < n; i++)
		ans = max(ans, max(dp[0][i], dp[1][i]));
	cout << ans << '\n';
}
