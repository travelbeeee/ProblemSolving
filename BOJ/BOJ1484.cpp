#include<iostream>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int cur = 2, past = 1, G;
	
	cin >> G;

	bool ans = false;
	while (1) {
		if (cur == past) break;

		int diff = cur * cur - past * past;
		if (diff == G) {
			cout << cur << '\n';
			ans = true;
			cur++;
		}
		else if (diff < G) {
			cur++;
		}
		else if (diff > G){
			past++;
		}
	}

	if (!ans) cout << -1 << '\n';

	return 0;
}
