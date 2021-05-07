/*
	BFS, MST

	로봇을 마음대로 복제할 수 있음
	--> 시작위치에서 열쇠를 탐방하다가 기존에 탐방한 다른 열쇠에서 탐방 안한 열쇠로 탐방을 진행할 수 있음!
	--> 최소횟수로 이동해야되니까 시작위치, 열쇠들을 트리형태로 만들자 (MST)
*/

#include<iostream>
#include<queue>
#include<vector>

using namespace std;

const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

int N, M;
int numberingMap[50][50];
string map[50];

// MST 만들기
int p[252];
priority_queue<pair<int, pair<int, int>>> pq;

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < N);
}

void BFS(int c, int x, int y) {
	queue<pair<pair<int, int>, int>> q;
	bool visited[50][50] = {};
	q.push({ {x, y}, 0 });
	visited[x][y] = true;

	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int curL = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++) {
			int nextX = cur.first + dx[k], nextY = cur.second + dy[k];
			if (!isInside(nextX, nextY)) continue;
			if (visited[nextX][nextY]) continue;
			if (map[nextX][nextY] == '1') continue;

			q.push({ {nextX, nextY}, curL + 1 });
			visited[nextX][nextY] = true;

			if (numberingMap[nextX][nextY]){
				pq.push({ -(curL + 1), { c, numberingMap[nextX][nextY]} });
			}
		}
	}
}

int find(int c) {
	if (p[c] < 0) return c;
	return p[c] = find(p[c]);
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

int getMST(void) {
	for (int i = 1; i <= M + 1; i++)
		p[i] = -1;

	int ans = 0;
	while (!pq.empty()) {
		int curL = -pq.top().first;
		pair<int, int> nodes = pq.top().second;
		pq.pop();

		if (find(nodes.first) == find(nodes.second)) continue;

		ans += curL;
		merge(nodes.first, nodes.second);
	}
	for (int i = 2; i <= M + 1; i++)
		if (find(1) != find(i)) ans = -1;
	return ans;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> map[i];
	
	int ind = 1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (map[i][j] == 'S' || map[i][j] == 'K')
				numberingMap[i][j] = ind++;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (numberingMap[i][j]) BFS(numberingMap[i][j], i, j);

	cout << getMST() << '\n';

	return 0;
}
