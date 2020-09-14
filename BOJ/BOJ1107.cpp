/*
  고장난 버튼을 제외하고 나머지 버튼들로 만들 수 있는 모든 경우를 Backtracking을 이용해 만들어서 visited 배열에 저장한다.
  
  그 후, 전체 가능한 경우들을 모두 순회하며 가장 최솟값을 찾는다.
  예를 들어, 1005가 이동해야 될 채널이고 "1001" 는 버튼을 4번 눌러 만들었다면 visited[1001] + abs(1005 - 1001) 을 하면 "1001"에서 1005로 이동하는 최소 횟수가 구해진다. 
*/

#include<iostream>
#include<queue>
#include<string>
#include<cstring>
#include<cmath>

using namespace std;

int N, visited[1000001] = {}, K;
bool isBroken[10] = {};
queue<int> q;

void makeChannel(string s) {
	for (int i = 0; i < 10; i++) {
		if (!isBroken[i]) {
			s += ('0' + i);
			if (stoi(s) <= 1000000) {
				visited[stoi(s)] = s.length();
				makeChannel(s);
			}
			s.pop_back();
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	memset(visited, -1, sizeof(visited));
	cin >> N >> K;
	for (int i = 0, x; i < K; i++) {
		cin >> x;
		isBroken[x] = 1;
	}
  
	// 만들 수 있는 모든 수 들을 만들어본다.
	if (!isBroken[0]) visited[0] = 1;
	for (int i = 1; i < 10; i++) {
		if (!isBroken[i]) {
			string t = "";
			t.push_back('0' + i);
			visited[i] = 1;
			makeChannel(t);
		}
	}
	visited[100] = 0;
  
  // 정답찾기
	int ans = 999999999;
	for (int i = 0; i <= 1000000; i++) {
		if (visited[i] != -1) {
			ans = min(ans, abs(N - i) + visited[i]);
		}
	}
	cout << ans << '\n';
	return 0;
}
