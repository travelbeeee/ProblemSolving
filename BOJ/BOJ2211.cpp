#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, M;
	pair<int, int> dist[1001] = {};
	vector<pair<int, int>> graph[1001];

	cin >> N >> M;
	for (int i = 0, a, b, c; i < M; i++) {
		cin >> a >> b >> c;
		graph[a].push_back({ b, c });
		graph[b].push_back({ a, c });
	}

	// 1번 컴퓨터에서 dijkstra 진행하기
	const int INF = 99999999;
	for (int i = 1; i <= N; i++)
		dist[i] = { INF, -1 };

	
	priority_queue<pair<int, int>> pq;
	pq.push({ 0, 1 });
	while (!pq.empty()) {
		pair<int, int> cur = pq.top();
		pq.pop();
		
		if (dist[cur.second].first < -cur.first)
			continue;

		for (pair<int, int> next : graph[cur.second]) {
			int nextDist = -cur.first + next.second;
			if (nextDist < dist[next.first].first) {
				dist[next.first] = { nextDist, cur.second };
				pq.push({ -nextDist, next.first });
			}
		}
	}
	
	// dijkstra 하는데 꼭 필요한 컴퓨터
	cout << N - 1 << '\n';
	for (int i = 2; i <= N; i++)
		cout << dist[i].second << ' ' << i << '\n';
}
