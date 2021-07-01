/*
	DP
  단순히 만족도만 DP를 이용해서 구하는 것이 아니라,
  만족도 DP를 채우기 위해서는 누적함 Dp 테이블이 추가로 필요하다.
  
	dp[i] := (i ~ N - 1) 까지 얻을 수 있는 최대 만족도
	--> dp[i] = max(i번 째 값을 포기하고 (i + 1 ~ N - 1) 에서 얻을 수 있는 최대 만족도,
					i번 째 값부터 누적합이 K 이상 되는지점(j)까지 가서 얻는 만족도 + dp[j + 1])
	
	sumDp[i] := (i번 째 값부터 누적합이 K 이상이 되는 지점, 거기까지의 누적합)
				없다면 초기화 상태인(0, 0) 이므로 누적합이 0이면 i에서 출발해도 없는 경우
*/
#include<iostream>

using namespace std;

int N, K, list[100000];
long long dp[100001];
pair<int, long long> sumDp[100000];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> list[i];

	// i에서 시작해서 어디까지 탐색해야 만족도를 채우는지 dp를 이용해 O(N)으로 구하기
	int i = N - 1, j = N - 1;
	long long s = 0;
	while (0 <= i) {
		s += list[i];
		if (s >= K) {
			while (i <= j && s - list[j] >= K) {
				s -= list[j];
				j--;
			}
			sumDp[i] = { j, s };
		}
		i--;
	}
  
  // dp초기화
	if (list[N - 1] > K) 
    dp[N - 1] = list[N - 1] - K;
  // dp채우기
	for (int i = N - 2; i >= 0; i--) {
		dp[i] = dp[i + 1];
		if (sumDp[i].second >= K) {
      dp[i] = max(dp[i], sumDp[i].second - K + dp[sumDp[i].first + 1]);
		}
	}

	cout << dp[0] << '\n';

	return 0;
}
