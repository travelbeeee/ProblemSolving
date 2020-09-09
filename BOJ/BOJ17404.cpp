/*
	1) 점화식
	dp[i][0] := i 번 째 집을 0(빨간)색으로 칠할 때 최소 비용
	-> dp[i][0] = color[i][0] + min(dp[i - 1][1], dp[i - 1][2] ) 가 성립
	다른 dp[i][1], dp[i][2] 도 마찬가지다

	2) 주의사항
	우리는 첫 번째 집이 마지막 집에 영향을 끼치는 원형 문제
	--> 첫 번째 집을 빨 / 초 / 파 3가지 경우로 각각 칠해서 각각 dp 배열을 구해본다.
	--> 첫 번째 집을 빨로 칠하면 dp 배열을 채우고, 마지막 집을 초 / 파로 선택한 값들만 사용한다.
	--> 마찬가지로 첫 번째 집을 초, 파로 칠하고 점화식을 이용해 dp배열을 채운 후 마지막 집을 다른 색깔로 선택한 값들만 이용한다.
*/
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int INF = 99999999;
int N, color[1000][3], ans = INF;
int dp[1000][3];

void getCost(void) {
	for (int i = 2; i < N; i++) {
		dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + color[i][0];
		dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + color[i][1];
		dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + color[i][2];
	}
	return;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);


	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> color[i][0] >> color[i][1] >> color[i][2];
	
	// 빨간집에서 시작했다고 가정하고 dp배열을 채워보자.
	dp[1][0] = INF, dp[1][1] = color[0][0] + color[1][1], dp[1][2] = color[0][0] + color[1][2];
	getCost();
	ans = min(ans, min(dp[N - 1][1], dp[N - 1][2]));

	// 초록집에서 시작했다고 가정하고 dp배열을 채워보자
	memset(dp, 0, sizeof(dp));
	dp[1][0] = color[0][1] + color[1][0], dp[1][1] = INF, dp[1][2] = color[0][1] + color[1][2];
	getCost();
	ans = min(ans, min(dp[N - 1][0], dp[N - 1][2]));

	// 파란집에서 시작햇다고 가정하고 dp배열을 채워보자
	memset(dp, 0, sizeof(dp));
	dp[1][0] = color[0][2] + color[1][0], dp[1][1] = color[0][2] + color[1][1], dp[1][2] = INF;
	getCost();
	ans = min(ans, min(dp[N - 1][0], dp[N - 1][1]));

	cout << ans << '\n';

	return 0;
}
