/*
	플로이드와샬 백트레킹

	N이 최대 10이므로 백트레킹을 이용해
	K번 행성에서 시작해 모든 행성을 순서대로 탐색하는 
	모든 경우의 수에 대해서 시간을 계산해볼 수 있다.

	이때, 이미 방문한 행성도 중복해서 갈 수 있으므로
	입력된 행성 간 이동 시간 배열을 플로이드와샬 알고리즘을 이용해 
	i번 행성에서 j번 행성으로 가는 최소 거리를 다시 계산해준다.
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N, K, ans;
int dist[10][10];
vector<int> order;
bool visited[10];

void backtracking(void) {
	if (order.size() == N) {
		int sum = 0;
		for (int i = 1; i < N; i++)
			sum += dist[order[i - 1]][order[i]];
		ans = min(ans, sum);
		return;
	}
	for (int i = 0; i < N; i++){
		if (!visited[i]) {
			visited[i] = true;
			order.push_back(i);
			backtracking();
			order.pop_back();
			visited[i] = false;
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> dist[i][j];

	// 플로이드와샬
	for (int k = 0; k < N; k++)
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
	
	ans = 99999999;
	order.push_back(K);
	visited[K] = true;
	backtracking();
	cout << ans << '\n';

	return 0;
}
