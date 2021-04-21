/*
  DP + BFS + Bitmasking
  
  1) 발전소가 최대 16개이므로 bitmasking을 이용해서 현재 돌아가는 발전소를 체크하자!
  2) 발전소 j를 작동시키는 방법은 커져있는 i로 작동시킬 수도 있고, i로 다른 발전소를 키고 작동시킬 수도 있고
    경우의 수가 굉장히 다양하므로 BFS + DP를 이용해서 모든 경우를 탐색해보자.
  3) 이때, bit로 현재 발전소 상태를 표현한 것과 string으로 표현한 표현식을 모두 가지고 있으면 다루기가 더 편해서
    두 정보를 모두 가지고 BFS 탐색을 진행한다.
*/
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

const int INF = 99999999;
int N, P;
int dp[(1 << 16)]; // dp[cur] := cur상태에서 최소 비용
int map[16][16];

bool checkFinish(string status) {
	int cnt = 0;
	for (int i = 0; i < N; i++) 
		if (status[i] == 'Y') cnt++;
	if (cnt >= P) return true;
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int bitStatus = 0;
	string status;

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	cin >> status >> P;

	for (int i = 0; i < (1 << N); i++)
		dp[i] = INF;

	for (int i = 0; i < N; i++)
		if (status[i] == 'Y') bitStatus = (bitStatus | (1 << i));

	int answer = INF;
	queue<pair<int, pair<int, string>>> q;
	dp[bitStatus] = 0;
	q.push({ 0,{bitStatus, status} });
	while (!q.empty()) {
		int cost = q.front().first;
		pair<int, string> curStatus = q.front().second;
		q.pop();

		if (checkFinish(curStatus.second)) {
			answer = min(answer, cost);
			continue;
		}
		if (dp[curStatus.first] < cost) continue;

		for (int i = 0; i < N; i++) {
			if (curStatus.second[i] == 'N') continue;
			for (int j = 0; j < N; j++) {
				if (curStatus.second[j] == 'Y') continue;
				// i 발전소를 이용해서 j 발전소를 켜자!
				string nextStrStatus = curStatus.second;
				nextStrStatus[j] = 'Y';
				pair<int, string> nextStatus = { curStatus.first | (1 << j), nextStrStatus };
				if (cost + map[i][j] < dp[nextStatus.first]) {
					dp[nextStatus.first] = cost + map[i][j];
					q.push({ cost + map[i][j], nextStatus });
				}
			}
		}
	}
	(answer == INF) ? (cout << -1 << '\n') : (cout << answer << '\n');

	return 0;
}
