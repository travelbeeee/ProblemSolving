/*
	굉장히 재미있던 문제!
	이분 탐색 + 다익스트라를 이용해면 시간 안에 해결을 할 수 있다.

	1) 이분탐색
	얼마 이하의 길들만 이용할지 를 기준으로 이분탐색을 진행한다.
	그러면 이분탐색의 범위는 1 ~ 10^9 가 된다.

	2) 다익스트라
	이분탐색으로 얼마 이하의 길들을 이용할지 정해졌다면,
	A지점에서 B지점으로 최단 거리를 구하면 된다.
	
	3)
	cost 이하의 길들만 이용해서 A에서 B로 가는 길이
	우리가 가지고 있는 C원 이하이면 갈 수 있으므로 답을 갱신한다.

	--> 이분탐색과 다익스트라를 이용하면 복잡도를 줄일 수 있다.
	--> O( log(10^9) * M * log(M))
*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
using ll = long long;

const ll INF = 1000000000000000;
int N, M, A, B, x, y;
ll C, c;
vector<pair<int, ll>> graph[100001];

// A에서 B지점까지 cost 이하의 길들만 이용해서 가기!
bool dijkstra(ll cost) {
	vector<ll> dist(N + 1, INF);
	priority_queue<pair<ll, int>> pq;
	pq.push({ 0L, A });
	dist[A] = 0;

	while (!pq.empty()) {
		ll curCost = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		if (dist[cur] < curCost) continue;

		for (pair<int, ll> next : graph[cur]) {
			if (next.second > cost) continue;
			ll nextDist = curCost + next.second;
			if (nextDist < dist[next.first]) {
				dist[next.first] = nextDist;
				pq.push({ -nextDist, next.first });
			}
		}
	}
	return (dist[B] <= C);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> A >> B >> C;
	for (int i = 0; i < M; i++){
		cin >> x >> y >> c;
		graph[x].push_back({ y, c });
		graph[y].push_back({ x, c });
	}

	// A에서 B로 탐색!!!
	ll left = 1, right = 1000000000, ans = -1;
	while (left <= right) {
		ll mid = (left + right) / 2;
		// A에서 B로 mid보다 작은 길들만 이용해서 최소로 고!
		if (dijkstra(mid)) { // 갈 수 있음!
			right = mid - 1;
			ans = mid;
		}
		else {
			left = mid + 1;
		}
	}
	cout << ans << '\n';
	return 0;
}
