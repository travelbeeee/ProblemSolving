/*
	다익스트라 백트레킹

	1) 
	백트레킹을 이용해 Market이 있는 Town을 방문하는 모든 경우의 수를 계산
	(최대 5! = 120 이라 저장가능)

	2) 
	Market이 있는 Town 들은 다익스트라로 먼저 최단거리를 구해놓는다.

	3) 
	Market이 없는 모든 Town을 시작 위치 후보로 삼아
	1)에서 구한 모든 경우의 순서대로 Town을 방문하며 최단 거리를 갱신
	이때, 2) 에서 구한 최단거리를 이용하면 된다.

*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

const int INF = 99999999;
int N, M, K, x, a, b, l, ans;
vector<pair<int, int>> graph[10001];
vector<int> markets(5); // market이 있는 Town
vector<int> dist[5]; // dist[i] := markets[i] 마을에서 시작한 다익스트라 결과
vector<vector<int>> orders; // 0 ~ K-1 모든 순열 조합
bool visited[10001]; // market이 있는 지점 체크

void backtracking(void) {
	vector<int> order;
	for (int i = 0; i < K; i++)
		order.push_back(i);
	do {
		orders.push_back(order);
	} while (next_permutation(order.begin(), order.end()));
}

vector<int> dijkstra(int cur) {
	vector<int> distance(N + 1, INF);
	distance[cur] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push({ 0, cur });

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		// 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 무시한다.
		if (distance[here] < cost) continue;
		// 인접한 정점들을 검사하며 경로 갱신!
		for (int i = 0; i < graph[here].size(); i++) {
			int next = graph[here][i].first;
			int nextDist = cost + graph[here][i].second;
			// 현재 정점을 거쳐서 이동하면 최단 거리가 갱신되는 경우
			if (nextDist < distance[next]) {
				distance[next] = nextDist;
				pq.push({ -nextDist, next });
			}
		}
	}

	return distance;
}

void func(int start) {
	// 모든 순열 조합에 대해서 거리 계산
	// start -> orders[i][0] --> orders[i][1] --> ... --> orders[i][K - 1] --> start
	for (int i = 0; i < orders.size(); i++) {
		int sum = dist[orders[i][0]][start];
		for (int j = 1; j < K; j++)
			sum += dist[orders[i][j - 1]][markets[orders[i][j]]];
		sum += dist[orders[i][K - 1]][start];
		ans = min(ans, sum);
	}
	return;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> M >> K;

	for (int i = 0; i < K; i++)
		cin >> markets[i];

	for (int i = 0; i < M; i++) {
		cin >> a >> b >> l;
		graph[a].push_back({ b, l });
		graph[b].push_back({ a, l });
	}

	backtracking();

	for (int i = 0; i < K; i++){
		visited[markets[i]] = true;
		dist[i] = dijkstra(markets[i]);
	}

	ans = INF;
	for (int i = 1; i <= N; i++) {
		if (visited[i]) continue; // market이 있는 Town은 계산 X
		func(i);
	}
	cout << ans << '\n';

	return 0;
}
