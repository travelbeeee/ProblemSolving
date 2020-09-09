/*
	그리디로 접근해 문제 해결
	
	1) 주어진 학생들의 신청서(a,b)를 b가 더 작고 b가 같다면 a가 더 작은 순으로 정렬한다.
	2) 정렬된 신청서를 순회하며 a부터 시작해 b까지 빌려줄 수 있는 책을 빌려준다.

	* (a1, b1) / (a2, b2) 가 있을 때 b1 < b2 라고 해보자.
	b1 < b2 이므로 (a2, b2) 는 (a1,b1) 신청서를 먼저 해결하고도 책 여유가 생김
	--> (a1, b1) 신청서를 먼저 처리하자!
	
	* (a1, b1) / (a2, b2) 가 있을 때 a1 < a2, b1 = b2 라고 해보자.
	b1 = b2인데, a1 < a2 이므로 (a1, b1) 신청서를 먼저 앞에서 해결하고 (a2, b2) 신청서를 해결하면 된다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int t;
	cin >> t;
	while (t--) {
		int N, M, ans = 0;
		pair<int, int> list[1000];
		bool checked[1001] = {};

		cin >> N >> M;
		for (int i = 0; i < M; i++)
			cin >> list[i].second >> list[i].first;

		sort(list, list + M);

		for (int i = 0; i < M; i++) {
			for(int j = list[i].second; j <= list[i].first; j++)
				if (!checked[j]) {
					checked[j] = true;
					break;
				}
		}

		for (int i = 1; i <= N; i++)
			if (checked[i]) ans++;

		cout << ans << '\n';

	}
}
