/*
	BFS탐색을 통해 
	( 현재 fullness, 물마신적있는지없는지 ) 에서
	갈 수 있는 모든 경우의 수로 탐색을 진행한다.
*/
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T, A, B, ans = -1;
	bool visited[500001][2] = {};

	cin >> T >> A >> B;

	queue<pair<int, bool>> q;
	q.push({ 0, 0 });
	visited[0][0] = 1;
	while (!q.empty()) {
		int curF = q.front().first;
		bool drinkWater = q.front().second;
		q.pop();

		ans = max(ans, curF);

		if (curF + A <= T && !visited[curF + A][drinkWater]) {
			q.push({ curF + A, drinkWater });
			visited[curF + A][drinkWater] = 1;
		}
		if (curF + B <= T && !visited[curF + B][drinkWater]) {
			q.push({ curF + B, drinkWater });
			visited[curF + B][drinkWater] = 1;
		}
		if (!drinkWater && !visited[curF / 2][!drinkWater]) {
			q.push({ curF / 2, !drinkWater });
			visited[curF / 2][!drinkWater] = 1;
		}
	}
	cout << ans << '\n';

	return 0;
}
