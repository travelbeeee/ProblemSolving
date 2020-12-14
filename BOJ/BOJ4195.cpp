/*
	좌표압축 이용!
	Map을 이용했더니 메모리 초과...
	좌표압축도 메모리 간당간당... ㅠ
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int T, N, p[200000];
string A, B;
vector<pair<string, string>> relations;
vector<string> list;

int find(int num) {
	if (p[num] < 0) return num;
	return p[num] = find(p[num]);
}

int merge(int a, int b) {
	int pA = find(a), pB = find(b);
	if (pA != pB) {
		p[pA] += p[pB];
		p[pB] = pA;
	}
	return -p[pA];
}

void init(void) {
	relations.clear();
	list.clear();
	for (int i = 0; i < 2 * N; i++)
		p[i] = -1;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> T;
	while (T--) {
		cin >> N;

		init();
		for (int i = 0; i < N; i++) {
			cin >> A >> B;
			relations.push_back({ A, B });
			list.push_back(A);
			list.push_back(B);
		}

		sort(list.begin(), list.end());
		list.erase(unique(list.begin(), list.end()), list.end());

		for (int i = 0; i < N; i++) {
			int x = lower_bound(list.begin(), list.end(), relations[i].first) - list.begin();
			int y = lower_bound(list.begin(), list.end(), relations[i].second) - list.begin();
			cout << merge(x, y) << '\n';
		}
	}
	return 0;
}
