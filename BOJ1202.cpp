/*
	그리디하게 문제를 해결 할 수 있는데,
	단순하게 가방에 담을 수 있는 보석 중에 가장 가치가 큰 보석을 담는 것이 최대 가치를 얻을 수 있을 것이다.
	--> 모든 가방에 대해서 모든 보석들을 탐색해 가장 큰 보석을 담는다. --> 복잡도 O(N * K) --> 시간초과
	
	--> 가방과 보석을 sorting 해놓고 탐색을 시작하자.
	내가 지금 작은 가방부터 탐색을 시작해 지금 넣을 수 있는 보석들 중에 가장 가치가 큰 값을 넣는다.
	그 다음 가방은 지금 가방보다 크기가 크므로 추가로 더 넣을 수 있는 보석들이 생길테고, 그 중 또 가치가 큰 값을 계속 넣는다.
	--> 넣을 수 있는 보석 중 가치가 가장 큰 보석이 의미가 있으므로 priority_queue 를 이용해 담을 수 있는 보석들을 추가로 담으며 알고리즘을 진행한다.
	--> O(N + K)에 문제 해결 가능!
	
	만약에 가치가  보석을 크기가 2인 가방으로 넣을 수 있고, 크기가 5인 가방으로도 넣을 수 있으면 우리는 어떤 가방에 담아도 의미가 없다.
	--> 크기가 작은 가방부터 최대한 좋은 가치를 넣어보자!
*/
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int N, K;
pair<int, int> jewelries[300000];
int bags[300000];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> jewelries[i].first >> jewelries[i].second;
	for (int i = 0; i < K; i++)
		cin >> bags[i];

	sort(jewelries, jewelries + N);
	sort(bags, bags + K);


	priority_queue<int> pq;
	int jewelry = 0;
	long long ans = 0;

	for (int i = 0; i < K; i++) {
		for (int j = jewelry; j < N; j++) {
			if (jewelries[j].first > bags[i]) break; // 지금 가방에 못 넣는 보석!
			pq.push({ jewelries[j].second });
			jewelry++;
		}
		if (!pq.empty()) {
			ans += pq.top();
			pq.pop();
		}
	}
	cout << ans << '\n';
}
