/*
	MST 크루스칼 Union-Find

	'친구의 친구는 친구다' 를 이용해 서로 친구인 
	애들끼리 미리 다 같은 집합으로 설정해놓는다.

	그 후, 크루스칼을 이용해 0번(준석) 이와 비용이 적은 친구들부터
	하나씩 Union을 해본다.
*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M, K, ans;
int p[10001];
vector<int> graph[10001];
priority_queue<pair<int, int>> costPQ; // { -i번과 친구 되는 비용, i번친구 }

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

void merge(int x, int y) {
	int pX = find(x), pY = find(y);
	if (pX == pY) return;
	if (p[pX] < p[pY]) {
		p[pX] += p[pY];
		p[pY] = pX;
	}
	else {
		p[pY] += p[pX];
		p[pX] = pY;
	}
}

bool check() {
	int p0 = find(0);
	for (int i = 1; i <= N; i++)
		if (p0 != find(i)) return false;
	return true;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> K;
	for (int i = 1, cost; i <= N; i++) {
		cin >> cost;
		costPQ.push({ -cost, i });
	}

	for (int i = 0, x, y; i < M; i++) {
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	// 친구의 친구들끼리 서로 연결해놓기
	for (int i = 0; i <= N; i++)
		p[i] = -1;
	for (int i = 1; i <= N; i++)
		for (int next : graph[i])
			merge(i, next);

	while (!costPQ.empty() && K) {
		pair<int, int> cur = costPQ.top();
		costPQ.pop();

		if (K < -cur.first) break; // 돈부족 --> 더이상 친구를 사귈 수 없음

		if (find(0) == find(cur.second)) continue; // 이미 친구인 경우

		ans += -cur.first;
		K -= -cur.first;

		merge(0, cur.second);
	}

	check() ? (cout << ans << '\n') : (cout << "Oh no\n");

	return 0;
}
