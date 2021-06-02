/*
  BFS DP
  
  시간초과로 굉장히 애를 먹은 문제
  
  1) 기존 코드
  list[0] ~ list[i - 1]로 만들 수 있는 모든 경우를 자료구조 Map을 이용해서 저장
  dp[0] 숫자 1개로 만든 숫자들
  dp[1] 숫자 2개로 만든 숫자들 --> dp[0]에 있는 값 + list[i] 로 갱신
  dp[2] 숫자 3개로 만든 숫자들 --> dp[1]에 있는 값 + list[i] 로 갱신
  --> 이러면 숫자 3개로 만든 경우의 수가 너무 많아져서 시간 초과 발생!
  
  2) 최적화 코드
  dp[0] / dp[1] 까지만 유지하고
  숫자 3개로 만든 경우를 현재 list[i] 값 - list[j] (0 <= j < i) 를 통해서 숫자 2개로 만든 경우랑 비교를 한다.
  --> 숫자 3개 x + y + z = list[i] 라면 x + y = list[i] - z 를 이용하면 최적화 할 수 있다.
*/ 
#include<iostream>
#include<map>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, list[5000];
	
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> list[i];
	
	map<int, bool> dp[2];

	dp[0].insert({ list[0], true });
	dp[1].insert({ list[0] * 2, true });


	int ans = 0;
	map<int, bool>::iterator it;

	for (int i = 1; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (dp[1].find(list[i] - list[j]) != dp[1].end()) {
				ans++;
				break;
			}
		}

		if (dp[0].find(list[i]) == dp[0].end())
			dp[0].insert({ list[i], true });

		for (it = dp[0].begin(); it != dp[0].end(); it++) {
			if (dp[1].find(it->first + list[i]) == dp[1].end()) {
				dp[1].insert({ it->first + list[i], true });
			}
		}
	}

	cout << ans << '\n';

	return 0;
}
