/*
	BFS / Backtracking

	robotDust 에는 robot / 먼지 위치 가 순서대로 들어가있다.
	먼저, 각각 robot, 먼지에서 BFS탐색을 통해 robot 과 먼지들 사이의 dist를 다 구해놓는다.

	그 후, 어떤 먼지부터 방문할지에 해당하는 모든 순서쌍에 대해서 위에서 구한 dist를 이용해 답을 갱신한다.
	당연히 방문 못하는 케이스에 대해서는 따로 처리해줘야한다.
	( 방문 못하는 경우를 고려하지 못해서 틀렸음! )

*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

const int INF = 9999999;
int N, M, ans, dist[11][11];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
char map[20][21];
bool selected[11];
vector<pair<int, int>> robotDust;

bool isInside(pair<int, int> p) {
	return (0 <= p.first && p.first < N && 0 <= p.second && p.second < M);
}

void BFS(int k) {
	queue<pair<int, int>> q;
	int visited[20][20] = {};

	q.push({ robotDust[k] });
	visited[robotDust[k].first][robotDust[k].second] = 1;

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			pair<int, int> next = { cur.first + dx[i], cur.second + dy[i] };
			if (!isInside(next)) continue;
			if (visited[next.first][next.second]) continue;
			if (map[next.first][next.second] == 'x') continue;
			visited[next.first][next.second] = visited[cur.first][cur.second] + 1;
			q.push(next);
		}
	}

	for (int i = 0; i < robotDust.size(); i++)
		dist[k][i] = visited[robotDust[i].first][robotDust[i].second] - 1;
}

int getDist(vector<int> v) {
	int res = 0;
	for (int i = 0; i < (int)v.size() - 1; i++){
		if (dist[v[i]][v[i + 1]] == 0) return INF;
		res += dist[v[i]][v[i + 1]];
	}
	return res;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	while (1) {
		cin >> M >> N;

		if (N == 0 && M == 0) break;

		ans = INF;
		robotDust.clear();

		for (int i = 0; i < N; i++)
			cin >> map[i];

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (map[i][j] == 'o') robotDust.push_back({ i, j });

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (map[i][j] == '*') robotDust.push_back({ i, j });

		vector<int> order(robotDust.size());
		for (int i = 0; i < robotDust.size(); i++){
			BFS(i);
			order[i] = i;
		}
		cout << "BFS 탐색 끝\n";
		// 어떤 먼지부터 닦을지 골라보자
		do {
			ans = min(ans, getDist(order));
		} while (next_permutation(order.begin() + 1, order.end()));

		(ans == INF) ? (cout << -1 << '\n') : (cout << ans << '\n');
	}	
}
