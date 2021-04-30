/*
  DP 탐색
  
  시간초과 때문에 고생한 문제...!
  일단 기본적인 아이디어는 똑같다.
  dp[i][j] := i번 지점에 j번의 skip을 진행하며 도착했을 때 최소값!
  --> dp[10001][21] 로 잡고 최대 10000 * 20 의 경우의 수만 생기므로 시간 초과가 안날거라고 생각!
  --> 그러나 기존코드처럼 단순 DFS로 모든 경우의 수를 탐색하면 앞에서 이미 더 큰 값으로 탐색하고
    그 후에 더 작은 값으로 탐색을 진행하는 상황이 많이 생기는 듯 하다
  --> priority_queue 를 이용한 다익스트라 알고리즘을 적용해서 똑같은 탐색 과정을 진행하는데
    값이 작은 애들부터 진행을 하자!
  
  [기존 코드]
  void DFS(int cur, long long cost, int skip) {
	if (cur == N) {
		ans = min(ans, cost);
		return;
	}
	if (dp[cur][skip] < cost) return;

	for (pair<int, long long> next : map[cur]) {
		if (skip < K && cost < dp[next.first][skip + 1]) { // 포장하기
			dp[next.first][skip + 1] = cost;
			DFS(next.first, cost, skip + 1);
		}
		if (cost + next.second < dp[next.first][skip]) {
			dp[next.first][skip] = cost + next.second;
			DFS(next.first, cost + next.second, skip);
		}
	}
}
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const long long INF = 99999999999;

int N, M, K;
long long ans = INF, dp[10001][21];
vector<pair<int, long long>> map[10001];

void set(void) {
	for (int i = 2; i <= N; i++)
		for (int j = 0; j <= K; j++)
			dp[i][j] = INF;
}


int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> K;
	for (int i = 0, A, B, C; i < M; i++) {
		cin >> A >> B >> C;
		map[A].push_back({ B, C });
		map[B].push_back({ A, C });
	}

	set();

	priority_queue<pair<long long, pair<int, int>>> pq;
	pq.push({ 0, { 0, 1 } });

	while (!pq.empty()) {
		long long cost = -pq.top().first;
		int skip = pq.top().second.first;
		int cur = pq.top().second.second;
		pq.pop();

		if (dp[cur][skip] < cost) continue;

		if (cur == N) {
			ans = min(ans, cost);
			continue;
		}

		for (pair<int, long long> next : map[cur]) {
			if (skip < K && cost < dp[next.first][skip + 1]) { // 포장하기
				dp[next.first][skip + 1] = cost;
				pq.push({ -cost, {skip + 1, next.first} });
			}
			if (cost + next.second < dp[next.first][skip]) {
				dp[next.first][skip] = cost + next.second;
				pq.push({ -(cost + next.second), {skip, next.first} });
			}
		}
	}
	cout << ans << '\n';

	return 0;
}
