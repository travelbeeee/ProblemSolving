#include<iostream>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, M, list[100000];

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> list[i];

	sort(list, list + N);

	int ans = 2000000001;
	int i = 0, j = 1;
	while (j < N) {
		if (list[j] - list[i] >= M) {
			ans = min(ans, list[j] - list[i]);
			i++;
		}
		else
			j++;
	}
	cout << ans << '\n';

	return 0;
}
