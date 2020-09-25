/*
	dp[i] := i번 째 날에 해당 스케쥴을 수행했을 때 얻을 수 있는 최대 이익
	--> dp[i]는 해당 스케쥴을 수행해서 얻는 이익 + 해당 스케쥴을 수행하고 난 나머지 스케쥴의 최대 이익 이 된다.
	:= schedule[i][1] + max(dp[i + schedule[i][0]] ~ dp[N]);
	
*/

#include<iostream>
#include<algorithm>

using namespace std;

int N;
int schedule[2][15];
int dp[15];

int main(void) {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> schedule[0][i] >> schedule[1][i];
	for (int i = N - 1; i >= 0; i--) {
		if (i + schedule[0][i] > N) { // i + 1 번 째 날 상담에 걸리는 시간이 퇴사 예정일 보다 더 길어버리면 수행을 못한다.
			dp[i] = 0;
			continue;
		}
		int m = 0;
		for (int j = i + schedule[0][i]; j < N; j++)
			m = max(m, dp[j]);
		dp[i] = m + schedule[1][i];
	}
	int ans = 0;
	for (int i = 0; i < N; i++)
		ans = max(ans, dp[i]);
	cout << ans;
}