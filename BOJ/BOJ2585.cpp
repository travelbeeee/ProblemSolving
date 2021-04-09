/*
  이분탐색 BFS

  연료통 크기의 범위 1 ~ 1415 를 이분탐색으로 연료통 크기를 고정시킨 후,
  도착지점까지 BFS 탐색을 통해 최소 경유 횟수를 구합니다!
  이 횟수가 K보다 작거나 같다면 해당 연료통 크기로 탐색이 가능하므로 답으로 갱시하고, 이분 탐색 범위를 낮춰보고
  불가능하다면 이분 탐색 범위를 올려봅니다.
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

// cur ~ next 까지 fuel 연료통으로 이동할 수 있는지 없는지!
bool canGo(pair<int, int> cur, pair<int, int> next, int fuel) {
	int dist = (cur.first - next.first) * (cur.first - next.first)
		+ (cur.second - next.second) * (cur.second - next.second);
	return (dist <= (10 * fuel) * (10 * fuel)); // 부동소수점 오류를 방지하기 위해 int로 계산
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	const int INF = 99999999;
	int N, K;
	vector<pair<int, int>> gasStation;

	cin >> N >> K;
	gasStation.push_back({ 0, 0 });
	for (int i = 0, x, y; i < N; i++) {
		cin >> x >> y;
		gasStation.push_back({ x, y });
	}
	gasStation.push_back({ 10000, 10000 });
	// 최악의 경우 연료통은 1415!
	int ans = INF;
	int left = 1, right = 1415;
	while (left <= right) {
		int mid = (left + right) / 2;
		queue<pair<pair<int, int>, int>> q;
		int visited[1002] = {};
		for (int i = 0; i <= N + 1; i++) visited[i] = INF;
		q.push({ {0, 0}, 0 });
		visited[0] = 0;

		while (!q.empty()) {
			pair<int, int> cur = q.front().first;
			int curL = q.front().second;
			q.pop();

			for (int i = 1; i <= N + 1; i++) {
				if (canGo(cur, gasStation[i], mid) && curL + 1 < visited[i]) {
					visited[i] = curL + 1;
					q.push({ {gasStation[i].first, gasStation[i].second}, curL + 1 });
				}
			}
		}
		if (visited[N + 1] <= K + 1) {
			ans = mid;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}

	cout << ans << '\n';

	return 0;
}
