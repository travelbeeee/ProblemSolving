#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	const int INF = 99999999;

	int N, M;
	int dp[105][105]; // dp[i][j] := i날까지 j개의 쿠폰을 가지고 있을 때 최소 비용
	bool cantUse[105] = {};

	cin >> N >> M;
	for (int i = 0, day; i < M; i++) {
		cin >> day;
		cantUse[day] = true;
	}
	for (int i = 0; i < 105; i++)
		for (int j = 0; j < 105; j++)
			dp[i][j] = INF;

	int minCost = INF;
	queue<pair<int, pair<int, int>>> q;
	q.push({ 0, {0, 0} });
	dp[0][0] = 0;

	while (!q.empty()) {
		int curDay = q.front().first;
		int curCost = q.front().second.first;
		int curCoupon = q.front().second.second;
		q.pop();

		if (curDay >= N) {
			minCost = min(minCost, curCost);
			continue;
		}

		if (dp[curDay][curCoupon] < curCost) continue;

		// 다음날 이용못하면 이용권 구매 할 필요가 없음
		if (cantUse[curDay + 1]) {
			if (curCost < dp[curDay + 1][curCoupon]) {
				dp[curDay + 1][curCoupon] = curCost;
				q.push({ curDay + 1, {curCost, curCoupon} });
			}
		}
		// 쿠폰 3장 사용
		if (curCoupon >= 3) {
			int nextCoupon = curCoupon - 3;
			if (curCost < dp[curDay + 1][nextCoupon]) {
				dp[curDay + 1][nextCoupon] = curCost;
				q.push({ curDay + 1, {curCost, nextCoupon} });
			}
		}

		// 이용권 구매
		int dayList[3] = { 1, 3, 5 }, costList[3] = { 10000, 25000, 37000 }, couponList[3] = { 0, 1, 2 };
		for (int i = 0; i < 3; i++) {
			int nextDay = curDay + dayList[i];
			int nextCost = curCost + costList[i];
			int nextCoupon = curCoupon + couponList[i];
			if (nextCost < dp[nextDay][nextCoupon]) {
				dp[nextDay][nextCoupon] = nextCost;
				q.push({ nextDay, {nextCost, nextCoupon} });
			}
		}
	}
	cout << minCost << '\n';

	return 0;
}
