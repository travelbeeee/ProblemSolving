/*
	# Union & Find 

	주어진 원(적군기지) 들을 다 순회하며 서로서로 같은 그룹에 속하는지 계산한다.
	두 점 사이의 거리가 2개의 반지름의 합보다 작거나 같다면 같은 그룹에 속하므로
	merge를 진행해준다.

	모든 순회가 끝났다면 그룹의 개수를 count 해준다.

*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int T, N, x, y, r;
int parent[3000];

int find(int a) {
	if (parent[a] < 0) return a;
	return find(parent[a]);
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

bool checkGroup(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
	int x = abs(a.first.first - b.first.first), y = abs(a.first.second - b.first.second);
	int r = a.second + b.second;
	int dist = x * x + y * y;
	
	if (dist <= r * r) return true;
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);


	cin >> T;
	while (T--) {
		cin >> N;

		vector<pair<pair<int, int>, int >> enemy;

		for (int i = 0; i < N; i++) {
			cin >> x >> y >> r;
			enemy.push_back({ {x, y}, r });
			parent[i] = -1;
		}

		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				if (checkGroup(enemy[i], enemy[j])) {
					merge(i, j);
				}
			}
		}
		int cnt = 0;
		for (int i = 0; i < N; i++)
			if (parent[i] < 0) cnt++;
		cout << cnt << '\n';
	}
}
