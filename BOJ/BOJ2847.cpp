#include<iostream>
#include<algorithm>
using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, list[100];
	int ans = 0;

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> list[i];

	for (int i = N - 1; i >= 0; i--){
		int minValue = 20001;
		for (int j = i + 1; j < N; j++) {
			minValue = min(minValue, list[j]);
		}
		if (list[i] < minValue) continue;
		else {
			ans += (list[i] - minValue) + 1;
			list[i] = minValue - 1;
		}
	}

	cout << ans << '\n';

	return 0;
}
