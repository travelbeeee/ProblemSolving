/*
	정렬 후 투 포인터
*/
#include<iostream>
#include<algorithm>

using namespace std;

int N, list[2000];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> list[i];

	sort(list, list + N);

	int ans = 0;
	for (int i = 0; i < N; i++) {
		int goal = list[i];
		int left = 0, right = N - 1;
		while (left < right) {
			if (left == i) {
				left++;
			}
			else if (right == i) {
				right--;
			}
			else if (list[left] + list[right] < goal) {
				left++;
			}
			else if (list[left] + list[right] > goal) {
				right--;
			}
			else {
				ans++;
				break;
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
