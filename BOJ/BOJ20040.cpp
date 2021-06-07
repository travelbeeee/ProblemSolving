/*
  Cycle 체크는 Union-Find
*/
#include<iostream>

using namespace std;

int N, M;
int p[500000];

int find(int cur) {
	if (p[cur] < 0) return cur;
	return p[cur] = find(p[cur]);
}

bool merge(int a, int b) {
	int pA = find(a), pB = find(b);
	if (pA == pB) return false;
	if (p[pA] < p[pB]) {
		p[pA] += p[pB];
		p[pB] = pA;
	}
	else {
		p[pB] += p[pA];
		p[pA] = pB;
	}
	return true;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		p[i] = -1;

	bool isFinished = false;
	for (int i = 1, a, b; i <= M; i++) {
		cin >> a >> b;
		if (!merge(a, b)) {
			cout << i << '\n';
			isFinished = true;
			break;
		}
	}
	if (!isFinished) cout << 0 << '\n';

	return 0;
}
