/*
  우선순위큐
  
  소 중에서는 빨리 도착하는 친구가 우선수위가 높고!
  대기 중인 소에서는 번호가 빠른 소가 우선 순위가 높다!
  --> 우선순위큐 2개를 이용해서 구현하자.
*/
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, time = 0, maxWaiting = -1;
	// 소 정보 --> 도착시간, (걸리는시간, 소번호) : 빨리 도착하는순!
	priority_queue<pair<int, pair<int, int>>> cows;
	// 대기열 --> 소번호, (도착시간, 걸리는시간) : 번호가 빠른순!
	priority_queue<pair<int, pair<int, int>>> waitingCows;

	cin >> N;
	for (int i = 0, a, t; i < N; i++) {
		cin >> a >> t;
		cows.push({ -a, {-t, -i} });
	}
	// 모든 소들이 다 먹을때까지
	while (!(cows.empty() && waitingCows.empty())) {
		// 현재 시간 전에 도착한애들! --> 대기열로 보내자!
		while (!cows.empty() && -cows.top().first <= time) {
			pair<int, pair<int, int>> cow = cows.top();
			cows.pop();

			waitingCows.push({ cow.second.second, {cow.first, cow.second.first} });
		}
		
		if (waitingCows.empty()) { // 대기열이 없음 --> 그냥 맨 앞 소를 먹이자!
			pair<int, pair<int, int>> cow = cows.top();
			cows.pop();
			maxWaiting = max(maxWaiting, 0);
			time = -cow.first + -cow.second.first;
		}
		else { // 대기열이 있음 --> 우선순위 높은 소를 
			pair<int, pair<int, int>> cow = waitingCows.top();
			waitingCows.pop();
			maxWaiting = max(maxWaiting, time + cow.second.first);
			time += -cow.second.second;
		}
	}
	cout << maxWaiting << '\n';

	return 0;
}
