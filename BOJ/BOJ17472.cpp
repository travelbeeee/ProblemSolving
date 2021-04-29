/*
	BFS + MST + Union&Find

	1) 섬마다 번호를 1부터 6까지 부여하며 좌표를 저장한다
		좌표 저장은 i섬에서 j섬으로 가는 최단 거리를 구하기 위해 저장!

	2) i섬에서 j섬으로 가는 최단 거리를 구하자!
		2-1) i섬이 모든 좌표와 j섬의 모든 좌표들을 비교해가며 다리를 이을 수 있으면
			MST를 위해 pq를 추가하자! 
			( 다리를 이으는 방법이 여러개라도 어차피 Cost가 작은 값을 먼저 Merge하므로 문제없다 )
			
			i섬의 좌표와 j섬의 좌표가 같은 row 값 혹은 같은 col 값이여야
			일단 다리를 이어볼 수 있고, 가는 길이 다 물이어야된다!

	3) 구한 거리를 이용해 MST를 구하자.
*/

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M, island = 1;
int map[10][10], p[7];
vector<pair<int, int>> islands[7];
priority_queue<pair<int, pair<int, int>>> pq;

const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < M);
}

// BFS탐색을 통해 섬에게 번호를 부여하고, 섬의 좌표를 모으자
void setIsland(void) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == -1) { 
				queue<pair<int, int>> q;
				q.push({ i, j });
				map[i][j] = island;
				islands[island].push_back({ i, j });
				while (!q.empty()) {
					pair<int, int> cur = q.front();
					q.pop();
					for (int k = 0; k < 4; k++) {
						int nextX = cur.first + dx[k], nextY = cur.second + dy[k];
						if (!isInside(nextX, nextY)) continue;
						if (map[nextX][nextY] == -1) {
							map[nextX][nextY] = island;
							q.push({ nextX, nextY });
							islands[island].push_back({ nextX, nextY });
						}
					}
				}
				island++;
			}
		}
	}
	for (int i = 1; i < island; i++)
		p[i] = -1;
}

int getDistance(pair<int, int> p1, pair<int, int> p2) {
	// 둘이 row값도 다르고 col값도 다름 --> 일직선으로 이을 수 없음!
	if (p1.first != p2.first && p1.second != p2.second) return 0;
	if (p1.first == p2.first) { // row값이 같음
		int i = p1.first;
		for (int j = min(p1.second, p2.second) + 1; j < max(p1.second, p2.second); j++) {
			if (map[i][j] != 0) return 0;
		}
		return max(p1.second, p2.second) - min(p1.second, p2.second) - 1;
	}
	if (p1.second == p2.second) { // col값이 같음
		int j = p1.second;
		for (int i = min(p1.first, p2.first) + 1; i < max(p1.first, p2.first); i++)
			if (map[i][j] != 0) return 0;
		return max(p1.first, p2.first) - min(p1.first, p2.first) - 1;
	}
}

// i섬에서 j섬으로 가는 최단 거리를 구하자
void setDistance(void) {
	for (int i = 1; i < island; i++) {
		for (int j = i + 1; j < island; j++) {
			// i섬, j섬
			for (int k = 0; k < islands[i].size(); k++) {
				for (int l = 0; l < islands[j].size(); l++) {
					// i섬의 k번째 좌표랑 j섬의 l번째 좌표가 이어질 수 있는지 체크!
					int dist = getDistance(islands[i][k], islands[j][l]);
					if (dist >= 2) { // 2 이상의 크기로 다리를 이을 수 있으면 저장!
						pq.push({ -dist, {i, j} });
					}
				}
			}
		}
	}
}

int find(int cur) {
	if (p[cur] < 0) return cur;
	return p[cur] = find(p[cur]);
}

void merge(int a, int b) {
	int pA = find(a), pB = find(b);
	if (pA == pB) return;
	if (p[pA] < p[pB]) {
		p[pA] += p[pB];
		p[pB] = pA;
	}
	else {
		p[pB] += p[pA];
		p[pA] = pB;
	}
}

int MST(void) {
	int res = 0;
	while (!pq.empty()) {
		int dist = -pq.top().first;
		pair<int, int> node = pq.top().second;
		pq.pop();

		if (find(node.first) == find(node.second)) continue;
		res += dist;
		merge(node.first, node.second);
	}
	// 모든 섬을 연결하는게 불가능하다면 -1
	for (int i = 1; i < island; i++)
		for (int j = i + 1; j < island; j++)
			if (find(i) != find(j)) return -1;
	return res;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == 1) map[i][j] = -1;

	setIsland();

	setDistance();

	cout << MST() << '\n';

	return 0;
}
