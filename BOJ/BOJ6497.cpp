/*
	Union & Find 를 이용해 MST를 만든다.

*/
#include<iostream>
#include<queue>

using namespace std;

int N, M, x, y, z, ans;
int parent[2000000];
priority_queue<pair<int, pair<int, int>>> pq;

void init(void) {
	for (int i = 0; i < N; i++) parent[i] = -1;
	ans = 0;
}

int find(int a) {
	if (parent[a] < 0) return a;
	return parent[a] = find(parent[a]);
}

void merge(int a, int b) {
	int pA = find(a), pB = find(b);
	if (pA == pB) return;

	if (parent[pA] < parent[pB]) {
		parent[pA] += parent[pB];
		parent[pB] = pA;
	}
	else {
		parent[pB] += parent[pA];
		parent[pA] = pB;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	while (1) {
		cin >> N >> M;
		if (N == 0 && M == 0) break;

		for (int i = 0; i < M; i++) {
			cin >> x >> y >> z;
			pq.push({ -z, { x,y } });
		}

		init();

		while (!pq.empty()) {
			pair<int, pair<int, int>> cur = pq.top();
			pq.pop();

			if (find(cur.second.first) == find(cur.second.second))
				ans += -cur.first;
			else
				merge(cur.second.first, cur.second.second);
		}

		cout << ans << '\n';

	}

	return 0;

}
