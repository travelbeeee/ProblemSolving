/*
  N개의 물건을 가지고 만들 수 있는 모든 경우의 수는 최대 2^30 가지가 되므로 시간 초과가 발생한다.
  따라서, (N / 2), (N / 2) 물건을 반으로 나눠서 각자 만들 수 있는 모든 경우의 수를 만들고
  그 경우의 수들로 조합해 무게가 C보다 작거나 같은 경우의 수를 체크해준다.
*/
#include<iostream>
#include<vector>

using namespace std;

const int MAX_VALUE = 1000000000;
int N, C, list[30];
vector<int> cases[2];

void backtracking(int s, int right, int value, int ind) {
	if (s == right) {
		cases[ind].push_back(value);
		return;
	}
	if(value + list[s] <= MAX_VALUE)
		backtracking(s + 1, right, value + list[s], ind);
	backtracking(s + 1, right, value, ind);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> C;
	for (int i = 0; i < N; i++)
		cin >> list[i];

	// 0 ~ (N / 2) - 1 을 조합해서 만들 수 있는 모든 경우의 수를 만들어보자
	backtracking(0, (N / 2), 0, 0);
	// (N / 2) ~ N  을 조합해서 만들 수 있는 모든 경우의 수를 만들어보자.
	backtracking((N / 2), N, 0, 1);

	int ans = 0;
	for (int i = 0; i < cases[0].size(); i++)
		for (int j = 0; j < cases[1].size(); j++)
			if (cases[0][i] + cases[1][j] <= C)
				ans++;
	
	/* 최적화를 위해 C보다 무게가 낮은 경우를 BinarySearch를 이용해 찾으면 더 최적화 시킬 수 있다.
	sort(cases[1].begin(), cases[1].end());
	for (int i = 0; i < cases[0].size(); i++) {
		int ind = 0, left = 0, right = cases[1].size() - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (cases[0][i] + cases[1][mid] <= C) {
				ind = mid;
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		ans += ind + 1;
	}
	*/
	cout << ans << '\n';

	return 0;
}
