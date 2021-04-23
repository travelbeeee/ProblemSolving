/*
  스택, 그리디
  
  기본원리
  1) 나보다 뒤에 큰 숫자가 없으면 내가 제일 큼!! --> 나는 삭제할 필요가 없음
  2) 나보다 뒤에 큰 숫자가 있고 거기까지 지워나갈 수 있으면 지우면됨!
  
  스택을 이용해서 
  1) 현재 내가 바라보고있는 숫자가 스택에 있는 값보다 크면 최대한 지운다
  2) 스택에 있는 값보다 작으면 스택에 쌓는다.
*/
#include<iostream>
#include<stack>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, K;
	string num;

	cin >> N >> K >> num;

	stack<char> s;
	for (int i = 0; i < N; i++) {
		if (!s.empty() && s.top() < num[i]) {
			while (K && !s.empty() && s.top() < num[i]) {
				s.pop();
				K--;
			}
		}
		s.push(num[i]);
	}
	while (K) {
		s.pop();
		K--;
	}

	string ans = "";
	while (!s.empty()) {
		ans.push_back(s.top());
		s.pop();
	}
	reverse(ans.begin(), ans.end());
	cout << ans << '\n';
	return 0;
}
