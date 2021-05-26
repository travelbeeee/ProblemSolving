/*
	우선순위큐

	우선순위큐를 이용해서 프로세스를 선택하는 알고리즘을 구현하면 된다.
	이때, 선택되지않은 프로세스들의 우선순위를 1 상승시키는 작업을
	선택된 프로세스의 우선순위를 1 감소시키는 작업으로 대신하면 된다.
*/
#include<iostream>
#include<queue>

using namespace std;

int main (void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T, N;
	priority_queue<pair<int, pair<int, int>>> pq; // { 우선순위, { 아이디, 시간 } }
	cin >> T >> N;
	for (int i = 0, A, B, C; i < N; i++) {
		cin >> A >> B >> C;
		pq.push({ C, { -A, B} });
	}

	for (int i = 0; i < T; i++) {
		pair<int, pair<int, int>> cur = pq.top();
		pq.pop();
		cur.first--;
		cur.second.second--;
		if (cur.second.second > 0) {
			pq.push(cur);
		}
		cout << -cur.second.first << '\n';
	}
}
