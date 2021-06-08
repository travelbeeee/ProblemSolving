#include<iostream>
#include<queue>

using namespace std;

const int INF = 99999999;
int N;
pair<int, int> dp[1000001];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 1; i <= N; i++)
		dp[i] = { INF, 0 };

	queue<pair<int, int>> q;
	q.push({ N, 0 });
	dp[N] = { 0, 0 };

	while (!q.empty()) {
		int curN = q.front().first;
		int curL = q.front().second;
		q.pop();

		if (curN == 1) continue;
		if (dp[curN].first < curL) continue;

		if (curN % 3 == 0 && curL + 1 < dp[curN / 3].first ) {
			dp[curN / 3] = { curL + 1, curN };
			q.push({ curN / 3, curL + 1 });
		}

		if (curN % 2 == 0 && curL + 1 < dp[curN / 2].first) {
			dp[curN / 2] = { curL + 1, curN };
			q.push({ curN / 2, curL + 1 });
		}
		if (1 < curN && curL + 1 < dp[curN - 1].first) {
			dp[curN - 1] = { curL + 1, curN };
			q.push({ curN - 1, curL + 1 });
		}
	}

	vector<int> road;
	int cur = 1;
	road.push_back(1);
	while (cur != N) {
		cur = dp[cur].second;
		road.push_back(cur);
	}

	cout << dp[1].first << '\n';
	for (int i = 0; i < road.size(); i++)
		cout << road[road.size() - 1-  i] << ' ';

	return 0;
}
