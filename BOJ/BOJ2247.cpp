#include<iostream>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	const long long M = 1000000;
	long long N, ans = 0;

	cin >> N;
	for (int div = 2; div <= (N / 2); div++) {
		ans += (div * ((N / div) - 1)) % M;
		ans %= M;
	}
	cout << ans << '\n';

	return 0;
}
