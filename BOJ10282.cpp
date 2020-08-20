/*
	시작점 C에서 시작해서 다른 system으로 이동하며 감염을 시키는 문제
	--> c에서 시작해서 다른 system까지 최단거리를 dijkstra를 이용해 구하자.
	--> 경로가 있다면 cnt, 경로 중 가장 긴 거리가 최대 시간!
*/

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int t;
	const int INF = 99999999;
	cin >> t;
	while (t--) {
		int n, d, c;
		vector<pair<int, int>> map[10001];

		cin >> n >> d >> c;
		for (int i = 0, a, b, c; i < d; i++) {
			cin >> a >> b >> c;
			map[b].push_back({ a, c });
		}

		vector<int> distance(n + 1, INF);
		distance[c] = 0;
		priority_queue<pair<int, int>> pq;
		pq.push({ 0, c });
		while (!pq.empty()) {
			int cost = -pq.top().first;
			int here = pq.top().second;
			pq.pop();

			if (distance[here] < cost) continue;
			for (int i = 0; i < map[here].size(); i++) {
				int next = map[here][i].first;
				int nextD = cost + map[here][i].second;
				if (nextD < distance[next]) {
					distance[next] = nextD;
					pq.push({ -nextD, next });
				}
			}
		}

		int cnt = 0, maxL = -INF;
		for(int i = 1; i <= n; i++)
			if (distance[i] != INF) {
				cnt++;
				maxL = max(maxL, distance[i]);
			}

		cout << cnt << ' ' << maxL << '\n';
	}
}
