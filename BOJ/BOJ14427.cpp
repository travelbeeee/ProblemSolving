/*
	Priority_Queue

	가장 작은 값과 그에 해당하는 인덱스를 출력해야되므로 pq를 이용해 모든 값들을 저장한다.
	이때, pq에서 뽑은 (값, 인덱스) 에서 list[인덱스] 값이 현재 뽑은 값과 다르다면
	이는 변경된 값이므로 pop을 진행하고 아니라면 출력해주면 된다.
*/
#include<iostream>
#include<queue>

using namespace std;

int N, M, list[100001];
priority_queue<pair<int, int>> pq;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> list[i];
		pq.push({ -list[i], -i });
	}
	cin >> M;

	for (int i = 0, Q, A, B; i < M; i++) {
		cin >> Q;
		if (Q == 2) {
			while (1) {
				pair<int, int> cur = pq.top();
				pq.pop();
				if (-cur.first == list[-cur.second]) { // 변경 안 된 친구!
					pq.push(cur);
					cout << -cur.second << '\n';
					break;
				}
			}
		}
		else {
			cin >> A >> B;
			list[A] = B;
			pq.push({ -B, -A });
		}
	}
}
