/*
  스택을 이용!
  1) 현재 스택의 Top 보다 값이 작음 --> 현재 스택의 Top에서 머리를 볼 수 있는 친구이므로 push
  2) 현재 스택의 Top 보다 값이 크거나 작음 
  --> 현재 스택의 Top에서 머리를 볼 수 없음
  --> pop하며 답갱신
*/
#include<iostream>
#include<stack>

using namespace std;

int N, list[80001];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> list[i];
	list[N] = 1000000001;

	long long ans = 0;
	stack<pair<int, int>> s;
	for (int i = 0; i <= N; i++) {
		if (s.empty() || s.top().second > list[i]) s.push({ i, list[i] });
		else {
			while (!s.empty() && s.top().second <= list[i]) {
				ans += 1LL * (i - s.top().first) - 1LL;
				s.pop();
			}
			s.push({ i, list[i] });
		}
	}
	cout << ans << '\n';

	return 0;
}
