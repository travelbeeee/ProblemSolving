/*
	주어진 선들을 sorting 해서 시작점이 앞인 애들부터 살펴보자.

	[1] 선 순회 
		lines[i] 와 lines[i - 1]을 비교했을 때 두 선은
		1) 이어진다
		 --> lines[i]를 lines[i - 1]과 이어진 선으로 갱신한다
		 --> lines[i].first = min(lines[i - 1].first, lines[i].first);
			 lines[i].second = max(lines[i - 1].second, lines[i].second);

		2) 이어지지않는다.
		 --> lines[i - 1] 에서 끊어진 것이므로 답을 갱신한다.
		 --> ans += (lines[i - 1].second - lines[i - 1].first);

	[2] 예외 처리
		1) 선이 1개인 경우 --> 따로 처리
		2) 마지막 선을 순회하는 경우 --> 무조건 답에 포함
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N;
	pair<int, int> lines[1000000];

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> lines[i].first >> lines[i].second;
	
	sort(lines, lines + N);

	long long ans = 0;
	if (N == 1) ans += lines[0].second - lines[0].first;

	for (int i = 1; i < N; i++) {
		// lines[i - 1] lines[i] 를 비교해보자.
		if (lines[i].first <= lines[i - 1].second) { // 만남 --> 선을 이어준다.
			lines[i].first = min(lines[i].first, lines[i - 1].first);
			lines[i].second = max(lines[i].second, lines[i - 1].second);
		}
		else { // 안만남 --> 답 갱신
			ans += 1LL * (lines[i - 1].second - lines[i - 1].first);
		}
		// 마지막 선은 무조건 답에 포함
		if (i == N - 1) ans += 1LL * (lines[i].second - lines[i].first);
	}
	cout << ans << '\n';
}
