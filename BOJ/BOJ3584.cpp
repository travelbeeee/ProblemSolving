/*
	그래프탐색

	입력되는 트리를 각 노드별로 부모와 자식을 따로 저장한다.
	공통 조상을 찾아야되는 두 노드가 같아질 때까지
	깊이가 깊은 쪽을 부모로 한 칸씩 올려본다.

*/
#include<iostream>
#include<vector>

using namespace std;

int T, N, depth[10001] = {};
int x, y;
int parent[10001];
vector<int> child[10001];

void init(void) {
	for (int i = 1; i <= N; i++){
		depth[i] = 0;
		parent[i] = 0;
		child[i].clear();
	}
}

void setDepth(int c, int p) {
	depth[c] = depth[p] + 1;
	for (int next : child[c])
		setDepth(next, c);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	while (T--) {
		cin >> N;

		init();
		for (int i = 0, a, b; i < N - 1; i++) {
			cin >> a >> b;
			parent[b] = a;
			child[a].push_back(b);
		}
		for (int i = 1; i <= N; i++)
			if (parent[i] == 0) { // i가 루트노드
				setDepth(i, 0);
				break;
			}
		cin >> x >> y;
		int res = x;
		while (x != y) {
			if (depth[x] > depth[y])
				x = parent[x];
			else
				y = parent[y];
			res = x;
		}
		cout << res << '\n';
	}
	return 0;
}
