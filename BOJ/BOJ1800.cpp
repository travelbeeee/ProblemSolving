/*
	BFS탐색 && BinarySearch

	1부터 N까지 탐색을 진행하는데 제일 비싼 K개는 무료로 이용 가능
	--> 기준점을 잡고 1부터 N까지 탐색하는데 기준점보다 큰 값이 몇 개인지 카운트하자!
	--> 결과가 K개보다 작거나 같다면 기준점으로 탐색이 가능! ( 정답 가능 )

	!참고
	left = 1 로 BinarySearch를 탐색하면 안된다!
	답이 0이 되는 경우가 있음
	when ??
	1 부터 N 까지 연결하는데 필요한 선이 K개보다 적음!
	--> cost가 필요없다
*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int INF = 999999;
int N, P, K, ans = -1;
vector<pair<int, int>> graph[1001];
int visited[1001] = {};

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> P >> K;
	for (int i = 0, x, y, c; i < P; i++) {
		cin >> x >> y >> c;
		graph[x].push_back({ y, c });
		graph[y].push_back({ x, c });
	}

	int left = 0, right = 1000000;
	while (left <= right) {
		int mid = (left + right) / 2;
		for (int i = 1; i <= N; i++)
			visited[i] = INF;

		visited[1] = 0;
		queue<pair<int, int>> q;
		q.push({ 1, 0 });
		
		while (!q.empty()) {
			int cur = q.front().first;
			int curCnt = q.front().second;
			q.pop();
      
			if (cur == N) continue;

			for (pair<int, int> next : graph[cur]) {
				if (mid < next.second && curCnt + 1 < visited[next.first] ) {
					visited[next.first] = curCnt + 1;
					q.push({ next.first, curCnt + 1 });
				}
				else if (next.second <= mid && curCnt < visited[next.first]) {
					visited[next.first] = curCnt;
					q.push({ next.first, curCnt });
				}
			}
		}
		// mid 기준으로 1부터 N까지 가는데 K개 이상이 쓰임
		if (visited[N] > K) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
			ans = mid;
		}
	}

	cout << ans << '\n';

	return 0;
}
