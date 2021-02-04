/*
	DP LCA
	
	DP를 이용한 LCA 알고리즘을 구현
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int N, M, x, y, maxDepth, maxLevel;
int depth[100001];
int dp[100001][17];
vector<int> graph[100001];

void set(int cur, int parent) {
	depth[cur] = depth[parent] + 1;	
	maxDepth = max(maxDepth, depth[cur]);
	dp[cur][0] = parent;

	int length = depth[cur] - 1, k = 1, powK = 2;
	while (powK <= length) {
		dp[cur][k] = dp[dp[cur][k - 1]][k - 1];
		k++;
		powK *= 2;
	}
	for (int next : graph[cur]) {
		if (depth[next]) continue;
		set(next, cur);
	}
}

int LCA(int x, int y) {
	// 먼저 높이가 더 높은 노드를 올려서 높이를 맞추자
	if (depth[x] != depth[y]) {
		if (depth[x] < depth[y])
			swap(x, y);
		// x를 y랑 같은 높이까지 올려주자 
		for (int i = maxLevel; i >= 0; i--)
			if (depth[y] <= depth[dp[x][i]]) {
				x = dp[x][i];
			}
	}
	int res = x;
	if (x != y) {
		for (int i = maxLevel; i >= 0; i--) {
			if (dp[x][i] != dp[y][i]) {
				x = dp[x][i];
				y = dp[y][i];
			}
			res = dp[x][i];
		}
	}
	return res;
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

	set(1, 0);

	// Dp[i][k] 에서 k의 최대값 := maxLevel
	maxLevel = (int)floor(log2(maxDepth - 1));

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> x >> y;
		cout << LCA(x, y) << '\n';
	}
	
	return 0;
}
