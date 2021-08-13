/*
	BFS + DP

	배열에서 '0'이 아닌 부분들은 순서만 지키면 되고
	우리가 원하는 부분 '0' 을 추가 할 수 있다
	--> 위/아래 배열에 대해 숫자인 부분과 빈칸이 몇 개 인지 count하자.

	또, 위 / 아래 배열을 현재 어디까지 곱해왔고, 
	위 배열의 빈 칸을 몇 번 이용했는지 알면
	아래 배열의 빈 칸을 몇 번 이용했는지 알 수 있으므로
	
	3차원 dp배열로 문제를 해결할 수 있다.
	
	dp[위 배열 어디까지 참조했는지][아래 배열 어디까지 참조했는지][위 배열 빈 칸 몇 번 이용했는지]
	dp[i][j][k] := 위 배열 i번 째, 아래 배열 j번 째를 참조하고 있고 위 배열 빈 칸 k번 사용했을 때 최대 값
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int INF = 99999999;

int N, upZero, downZero;
int dp[405][405][405];
vector<int> up;
vector<int> down;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	for (int i = 0; i < 405; i++)
		for (int j = 0; j < 405; j++)
			for (int k = 0; k < 405; k++)
				dp[i][j][k] = -INF;

	cin >> N;
	for (int i = 0, x; i < N; i++) {
		cin >> x;
		if (x == 0) upZero++;
		else up.push_back(x);
	}
	for (int i = 0, x; i < N; i++) {
		cin >> x;
		if (x == 0) downZero++;
		else down.push_back(x);
	}

	queue<pair<pair<int, int>, pair<int, int>>> q;
	q.push({ {0, 0}, {0, 0} });
	dp[0][0][0] = 0;

	int ans = -INF;
	while (!q.empty()) {
		int upInd = q.front().first.first;
		int downInd = q.front().first.second;
		int upZeroInd = q.front().second.first;
		int downZeroInd = (upInd + upZeroInd) - downInd;
		int sum = q.front().second.second;

		q.pop();

		if (upInd == up.size() && downInd == down.size() &&
			upZeroInd == upZero && downZeroInd == downZero) {
			ans = max(ans, dp[upInd][downInd][upZeroInd]);
			continue;
		}

		if (sum < dp[upInd][downInd][upZeroInd])
			continue;

		// Up * Dowb
		if (upInd < up.size() && downInd < down.size()) {
			int newSum = sum + up[upInd] * down[downInd];
			if (dp[upInd + 1][downInd + 1][upZeroInd] < newSum) {
				q.push({ {upInd + 1, downInd + 1}, {upZeroInd, newSum} });
				dp[upInd + 1][downInd + 1][upZeroInd] = newSum;
			}
		}
		// Up * DownZero
		if (upInd < up.size() && downZeroInd < downZero) {
			if (dp[upInd + 1][downInd][upZeroInd] < sum) {
				q.push({ {upInd + 1, downInd}, {upZeroInd, sum} });
				dp[upInd + 1][downInd][upZeroInd] = sum;
			}
		}
		// Down * UpZero
		if (downInd < down.size() && upZeroInd < upZero) {
			if (dp[upInd][downInd + 1][upZeroInd + 1] < sum) {
				q.push({ {upInd, downInd + 1}, {upZeroInd + 1, sum} });
				dp[upInd][downInd + 1][upZeroInd + 1] = sum;
			}
		}
		// UpZero * DownZero
		if (upZeroInd < upZero && downZeroInd < downZero) {
			if (dp[upInd][downInd][upZeroInd + 1] < sum) {
				q.push({ {upInd, downInd}, {upZeroInd + 1, sum} });
				dp[upInd][downInd][upZeroInd + 1] = sum;
			}
		}
	}
	cout << ans << '\n';

	return 0;
}
