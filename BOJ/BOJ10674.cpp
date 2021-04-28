/*
  DP + BFS
  
  A -> B로 가는 단방향 그래프이고 cost가 최대 100이므로
  N이 최대값 100이고, 최대한 많은 노드를 거쳐가도 cost가 10000을 넘지않음!
  --> dp[cur][character][cost] 배열을 이용해서 현재 노드까지 어떤 케릭터(Bessie, Elsie)가 어떤 cost로 왔는지 모두 저장하자!
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, M;
vector<pair<int, int>> map[101][2];
bool dp[101][2][10000];

void DFS(int cur, int cost, int character) {
	if (cur == N) return;

	for (pair<int, int> next : map[cur][character]) {
		int nextCost = cost + next.second;
		// nextCost 로 이미 그 전에 같은 가격으로 도착한적이 있다면 끝!
		if (dp[next.first][character][nextCost]) continue;
		dp[next.first][character][nextCost] = true;
		DFS(next.first, nextCost, character);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0, A, B, C, D; i < M; i++) {
		cin >> A >> B >> C >> D;
		map[A][0].push_back({ B, C });
		map[A][1].push_back({ B, D });
	}

	dp[1][0][0] = dp[1][1][0] = true;
	DFS(1, 0, 0); // 1에서 시작해서 처음 cost는 0이고 Bessie(0)
	DFS(1, 0, 1);// 1에서 시작해서 처음 cost는 0ㅇ고 Elsie(1)

	int ans = -1;
	for (int i = 0; i < 10000; i++)
		if (dp[N][0][i] && dp[N][1][i]) {
			ans = i;
			break;
		}

	(ans == -1) ? (cout << "IMPOSSIBLE\n") : (cout << ans << '\n');

	return 0;
}
