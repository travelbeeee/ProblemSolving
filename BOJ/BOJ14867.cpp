/*
  BFS탐색
  
  2차원 배열로 Visited 를 선언하게 되면 10^5 * 10^5 로 메모리 초과가 발생하므로,
  자료구조 Map을 이용해서 visited 
*/
#include<iostream>
#include<map>
#include<queue>

using namespace std;

int a, b, A, B;
map<pair<int, int>, int> visited;
queue<pair<pair<int, int>, int>> q;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> a >> b >> A >> B;

	q.push({ {0, 0}, 0 });
	visited.insert({ {0, 0}, 0 });
	while (!q.empty()) {
		pair<int, int> cur = q.front().first;
		int curL = q.front().second;
		q.pop();

		if (visited[{cur.first, cur.second}] < curL) continue;
		if (cur.first == A && cur.second == B) break;

		// Fill(A)
		if (cur.first < a) {
			if (visited.find({ a, cur.second }) == visited.end() ||
				curL + 1 < visited[{a, cur.second}]) {
				visited.insert({ {a, cur.second}, curL + 1 });
				q.push({ {a, cur.second}, curL + 1 });
			}
		}
		// Fill(B)
		if (cur.second < b) {
			if (visited.find({ cur.first, b }) == visited.end() ||
				curL + 1 < visited[{cur.first, b}]) {
				visited.insert({ {cur.first, b}, curL + 1 });
				q.push({ {cur.first, b}, curL + 1 });
			}
		}
		// Empty(A)
		if (0 < cur.first) {
			if (visited.find({ 0, cur.second }) == visited.end() ||
				curL + 1 < visited[{0, cur.second}]) {
				visited.insert({ {0, cur.second}, curL + 1 });
				q.push({ {0, cur.second}, curL + 1 });
			}
		}
		// Empty(B)
		if (0 < cur.second) {
			if (visited.find({ cur.first, 0 }) == visited.end() ||
				curL + 1 < visited[{cur.first, 0}]) {
				visited.insert({ {cur.first, 0}, curL + 1 });
				q.push({ {cur.first, 0}, curL + 1 });
			}
		}
		int newA, newB, diff;
		// Move A to B
		// A물통이 줄 수 있는 양과 B물통이 받을 수 있는 양 중 작은 값이 이동 가능!
		diff = min(b - cur.second, cur.first);
		newA = cur.first - diff;
		newB = cur.second + diff;
		if (visited.find({ newA, newB }) == visited.end() ||
			curL + 1 < visited[{newA, newB}]) {
			visited.insert({ {newA, newB}, curL + 1 });
			q.push({ { newA, newB}, curL + 1 });
		}
		// Move B to A
		diff = min(a - cur.first, cur.second);
		newA = cur.first + diff;
		newB = cur.second -  diff;
		if (visited.find({ newA, newB }) == visited.end() ||
			curL + 1 < visited[{newA, newB}]) {
			visited.insert({ {newA, newB}, curL + 1 });
			q.push({ { newA, newB}, curL + 1 });
		}
	}
	visited.find({ A, B }) == visited.end() ? (cout << -1 << '\n') : (cout << visited[{A, B}] << '\n');

	return 0;
}
