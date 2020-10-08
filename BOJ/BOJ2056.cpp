/*
	위상정렬

	mTime[i] := i번 째 노드를 작업하기 위해 필요한 작업 시간
			:= i번 째 선행 작업들을 완료하는데 필요한 시간 중 가장 큰 값

	--> 위상정렬을 통해 i번 째 작업의 선행 작업들을 진행하며 mTime[i] 를 갱신
	--> ( 작업번호, mTime ) 을  통해 위상정렬을 진행 
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N,  time[10001], mTime[10001] = {}, inDegree[10001] = {}, ans = 0;
	vector<int> graph[10001];

	cin >> N;
	for (int i = 1, x, y; i <= N; i++) {
		cin >> time[i] >> x;
		for (int j = 0; j < x; j++) {
			cin >> y;
			graph[y].push_back(i);
			inDegree[i]++;
		}
	}

	queue<pair<int, int>> q;
	for (int i = 1; i <= N; i++)
		if (!inDegree[i]) q.push({ i, time[i] });

	while (!q.empty()) {
		int c = q.front().first, t = q.front().second;
		q.pop();

		ans = max(ans, t);

		for (int i = 0; i < graph[c].size(); i++) {
			int next = graph[c][i];
			inDegree[next]--;
			mTime[next] = max(mTime[next], t + time[next]);
			if (inDegree[next] == 0)
				q.push({ next, mTime[next] });
		}
	}

	cout << ans << '\n';

	return 0;
}
