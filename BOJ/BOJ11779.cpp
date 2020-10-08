/*
	다익스트라

	dist[i] := s에서 출발해서 i까지 가는데 { 최소비용, 전에 방문한 도시 } 를 저장하면 경로를 금방 찾을 수 있다.
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int INF = 99999999;
int N, M, s, e;
vector<pair<int, int>> graph[1001];
pair<int, int> dist[1001];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0, x, y, z; i < M; i++) {
		cin >> x >> y >> z;
		graph[x].push_back({ y, z });
	}
	cin >> s >> e;

	for (int i = 1; i <= N; i++) dist[i] = { INF, 0 };

	priority_queue<pair<int, int>> pq;

	pq.push({ 0, s });
	while (!pq.empty()) {
		int cost = -pq.top().first, cur = pq.top().second;
		pq.pop();
		if (dist[cur].first < cost) continue;

		for (int i = 0; i < graph[cur].size(); i++) {
			int next = graph[cur][i].first, nextCost = cost + graph[cur][i].second;
			if (nextCost < dist[next].first) {
				dist[next] = { nextCost, cur };
				pq.push({ -nextCost, next });
			}
		}
	}

	int c = e;
	vector<int> path;

	while (1) {
		path.push_back(c);

		if (c == s) break;

		c = dist[c].second;
	}

	reverse(path.begin(), path.end());

	cout << dist[e].first << '\n';
	cout << path.size() << '\n';
	for (int i = 0; i < path.size(); i++)
		cout << path[i] << ' ';

	return 0;
}
