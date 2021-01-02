/*
	트리DP BFS

	칭찬을 다 저장해둔 다음에 루트노드부터 리프노드까지
	칭찬을 쌓아가며 탐색을 진행한다. (BFS)
*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n, m;
int w[100001], ans[100001];
vector<int> c[100001];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n >> m;
	for (int i = 1, x; i <= n; i++){
		cin >> x; // i번 직원의 상사가 x번 --> x번의 부하는 i번
		if (x == -1) continue;
		c[x].push_back(i);
	}

	for (int i = 0, x, y; i < m; i++) {
		cin >> x >> y;
		w[x] += y;
	}

	queue<pair<int, int>> q;
	q.push({ 1, 0 });

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		ans[cur.first] = cur.second;

		for (int next : c[cur.first]) {
			q.push({ next, cur.second + w[next] });
		}
	}

	for (int i = 1; i <= n; i++)
		cout << ans[i] << ' ';

	return 0;
}
