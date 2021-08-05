/*
	N개로 만들 수 있는 모든 경우의 수를 만들어본다.
	백트레킹을 이용해 2^N 으로 해결할 수도 있지만,
	최대 범위인 200,0000 * N 으로 해결해도 N이 20이므로 가능하다.
*/

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N, list[20];
bool isMaked[2000001];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> list[i];

	sort(list, list + N);

	isMaked[0] = true;
	for (int i = 0; i < N; i++) {
		vector<int> newSum;
		for (int j = 0; j <= 2000000; j++) {
			if (isMaked[j]) {
				newSum.push_back(j + list[i]);
			}
		}
		for (int sum : newSum)
			isMaked[sum] = true;
	}
	for (int i = 1;; i++) {
		if (!isMaked[i]) {
			cout << i << '\n';
			break;
		}
	}
	return 0;
}
