/*
	dp[i][j][k] := 
	i가 0이면 악마의 다리, 1이면 천사의 다리의 k번 째까지 탐생글 진행했고
	마법두루마리의 j번 째 문자열을 찾아야 될 때의 경우의 수
*/
#include<iostream>

using namespace std;

int N, M;
int dp[2][21][101];
string magic;
string bridge[2];

int func(int m, bool down, int b) {
	if (m >= M)
		return dp[down][m][b] = 1;
	if (b >= N)
		return 0;

	if (dp[down][m][b])
		return dp[down][m][b];

	for (int next = b; next < N; next++) {
		if (magic[m] == bridge[!down][next]) {
			dp[down][m][b] += func(m + 1, !down, next + 1);
		}
	}
	return dp[down][m][b];
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> magic >> bridge[0] >> bridge[1];

	N = bridge[0].length();
	M = magic.length();

	int ans = 0;
	ans += func(0, false, 0);
	ans += func(0, true, 0);

	cout << ans << '\n';

	return 0;
}
