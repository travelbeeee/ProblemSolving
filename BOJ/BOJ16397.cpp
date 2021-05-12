/*
  BFS탐색
  
*/
#include<iostream>
#include<queue>
#include<cmath>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	const int INF = 99999999;
	int N, T, G;
	int dp[100000] = {};

	cin >> N >> T >> G;
	
	for (int i = 0; i < 100000; i++)
		dp[i] = INF;

	queue<pair<int, int>> q;
	q.push({ N, 0 });
	dp[N] = 0;

	while (!q.empty()) {
		int curN = q.front().first, curL = q.front().second;
		q.pop();

		if (curN == G) break;
		if (curL >= T) continue; // T번 누르면 더 진행할필요없음
		if (dp[curN] < curL) continue; // 이미 더 빠르게 도착한상황

		if (curN + 1 <= 99999 && curL + 1 < dp[curN + 1]) {
			dp[curN + 1] = curL + 1;
			q.push({ curN + 1, curL + 1 });
		}

		if (2 * curN <= 99999) {
			// 2 * curN 의 가장 앞 자리수를 따자.
			int tempN = 2 * curN, digits = 0;
			while (tempN >= 10) {
				tempN /= 10;
				digits++;
			}
			if (tempN == 0) continue;
			int nextN = 2 * curN - (int)pow(10, digits);
			if (curL + 1 < dp[nextN]) {
				dp[nextN] = curL + 1;
				q.push({ nextN, curL + 1 });
			}
		}
	}

	dp[G] == INF ? (cout << "ANG") : (cout << dp[G]);

	return 0;
}
