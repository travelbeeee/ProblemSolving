/*
	라인스위핑

	수업 시간을 수직선에 N개의 선으로 표현하자.
	N개의 선이 제일 많이 겹치는 순간만큼은
	강의실이 있어야한다.
*/
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, s, t;
	priority_queue<pair<int, int>> pq;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> s >> t;
		pq.push({ -s, -1 });
		pq.push({ -t, 1 });
	}

	int maxRes = 0, curRes = 0;
	while (!pq.empty()) {
		pair<int, int> cur = pq.top();
		pq.pop();

		curRes += -cur.second; // 시작지점이면 +1 끝지점이면 -1
		maxRes = max(maxRes, curRes);
	}

	cout << maxRes << '\n';

	return 0;
}
