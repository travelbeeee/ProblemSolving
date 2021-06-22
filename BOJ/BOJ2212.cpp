/*
* Greedy
* 
* K개의 집중국을 설치할 수 있고, N개의 센서 사이의 N - 1개의 간격에 대해서 생각해보자.
* 집중국을 설치한다는 것은 센서 사이의 간격을 하나 지운다고 생각하면 된다.
* --> (K - 1)개의 간격을 지울 수 있다.
* --> (N - 1)개의 간격 중 가장 큰 값들을 최대 (K - 1)개 지울 수 있다.
* 
* 
* BinarySearch로 접근했으나... Greedy하게 해결할 수 있는 문제였다.
*/
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, K, list[10000];
	priority_queue<int> pq;

	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> list[i];

	sort(list, list + N);

	int res = 0;
	for (int i = 0; i < N - 1; i++){
		res += list[i + 1] - list[i];
		pq.push(list[i + 1] - list[i]);
	}

	while (!pq.empty() && 1 < K) {
		res -= pq.top();
		pq.pop();
		K--;
	}

	cout << res << '\n';

	return 0;
}
