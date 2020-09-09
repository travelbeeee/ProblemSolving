/*
  A배열을 기준으로 B배열 값들의 Index를 얻는다
  그 후, Index 배열에 대해서 LIS를 구하면 된다.
  O(NlogN)
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int LIS(vector<int> v) {
	const int INF = 99999999;
	int N = v.size();
	vector<int> Dp(N + 1, INF);
	int longest = 1;
	Dp[0] = -INF;
	Dp[1] = v[0];
	for (int cur : v) {
		if (Dp[longest] < cur) {
			longest++;
			Dp[longest] = cur;
		}
		else {
			vector<int>::iterator it = lower_bound(Dp.begin(), Dp.end(), cur);
			*it = cur;
		}
	}
	int ans = 0;
	for (int i = 1; i <= N; i++)
		if (Dp[i] != INF) ans = i;
	return ans;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N;
	cin >> N;
	
	vector<int> A(N);
	vector<int> temp(N);
	vector<int> index(N);

	for (int i = 0; i < N; i++)
		cin >> A[i];

	for (int i = 0, x; i < N; i++) {
		cin >> x;
		temp[x - 1] = i;
	}

	for (int i = 0; i < N; i++)
		index[i] = temp[A[i] - 1];

	cout << LIS(index);
	
}
