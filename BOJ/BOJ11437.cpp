#include<iostream>
#include<vector>

using namespace std;

int N, M, x, y;
vector<int> graph[50001];
int parent[50001]; // 부모노드의 번호
int depth[50001]; // 트리 내 깊이

int LCA(int a, int b) {
	// 항상 b가 더 깊게 만들자
	if (depth[a] > depth[b]) {
		int temp = a;
		a = b;
		b = temp;
	}
	while (depth[b] != depth[a]) {
		b = parent[b];
	}
	while (a != b) {
		a = parent[a];
		b = parent[b];
	}
	return a;
}

void dfs(int cur) {
	for (int next : graph[cur]) {
		if (parent[next] != 0) continue;
		parent[next] = cur;
		depth[next] = depth[cur] + 1;
		dfs(next);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	parent[1] = -1;
	dfs(1);

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> x >> y;
		cout << LCA(x, y) << '\n';
	}
}
