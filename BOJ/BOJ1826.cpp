/*
	처음에는 BFS탐색으로 문제를 해결하려다 시간초과에 직면!

	연료를 중심으로 그리디하게 접근해야된다.
	1) 현재 가지고 있는 연료 = 현재 내가 갈 수 있는거리
	2) 내가 들릴 수 있는 주유소들이 있다면, 
	주유소에서 얻을 수 있는 연료 + 내가 가지고 있는 연료 = 주유소에 들려서 갈 수 있는 거리 가 된다.
	--> 내가 갈 수 있는 주유소 중에서는 연료를 가장 많이 주는 곳이 의미가 있다!
	--> 왜냐하면 내가 가지고 있는 연료는 동일하므로 연료를 많이 얻어야 더 멀리 갈 수 있음

	예를 들어, 내가 연료가 10인 상태에서 시작하고 (2,4) / (6,5) 에 주유소가 있다고 하자.
	(2, 4) 주유소는 연료를 2만 쓰고 4를 얻을 수 있고,
	(6, 5) 주유소는 연료를 6이나 쓰고 5를 얻을 수 있으므로 (2,4) 가 더 유리해보인다.
	--> 이게 함정!!
	(2, 4) 를 들리면 연료가 12가 남고 (6, 5) 를 들리면 연료가 9 가 남지만 
	실제로 (2, 4)를 들리면 나는 최대 14까지 갈 수 있고 (6, 5)를 들리면 나는 최대 15까지 갈 수 있음
	--> 내가 갈 수 있는 주유소 중에서 연료를 제일 많이 주는 주유소들을 계속 탐색해야됨!
	--> priority_queue 를 이용해서 갈 수 있는 주유소의 연료를 다 push하고 연료를 제일 많이 주는 주유소를 탐색하자.

*/

#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, L, P;
	pair<int, int> gasStation[10000];
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> gasStation[i].first >> gasStation[i].second;
	cin >> L >> P;

	sort(gasStation, gasStation + N);

	// P연료를 가지고 L까지 가야된다!
	priority_queue<int> pq;

	int curP = 0, curL = P, ans = 0;
	while (curL < L) {
		while (curP < N && gasStation[curP].first <= curL) {
			pq.push(gasStation[curP++].second);
		}
		if (pq.empty()) { // L 에 도착도 못했고, 더 이상 갈 곳도 없음.
			ans = -1;
			break;
		}
		curL += pq.top();
		pq.pop();
		ans++;
	}
	cout << ans << '\n';
	return 0;
}
