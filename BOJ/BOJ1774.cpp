/*
	MST Kruskal 

	Kruskal 알고리즘을 이용해서 MST를 만든다.
	이때, 이미 연결된 통로들은 road를 만들지 않아도 되므로
	거리를 답에 추가하지 않고 그냥 사용한다.

	* 주의할 점 *
	좌표가 최대 0 ~ 10^6 이므로 
	피타고라스를 이용해 거리를 구할 떄 int 범위를 초과한다.

*/
#include<iostream>
#include<queue>
#include<cmath>

using namespace std;

using ll = long long;

int N, M;
int p[1001];
pair<int, int> point[1001];
double ans = 0;
priority_queue<pair<ll, pair<int, int>>> pq;

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
	return;
}

void setDist(void) {
	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {
			ll dist = 1LL * (point[i].first - point[j].first) * (point[i].first - point[j].first)
				+ 1LL * (point[i].second - point[j].second) * (point[i].second - point[j].second);
			pq.push({ -dist, {i, j} });
		}
	}
}

void kruskal(void) {
	while (!pq.empty()) {
		ll curDist = pq.top().first;
		pair<int, int> curP = pq.top().second;

		pq.pop();

		if (find(curP.first) == find(curP.second))
			continue;

		merge(curP.first, curP.second);
		ans += sqrt(-curDist);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		cin >> point[i].first >> point[i].second;
	for (int i = 1; i <= N; i++)
		p[i] = -1;
	for (int i = 0, x, y; i < M; i++) {
		cin >> x >> y;
		merge(x, y);
	}

	setDist();
	
	kruskal();

	cout << fixed;
	cout.precision(2);
	cout << ans << '\n';

	return 0;
}
