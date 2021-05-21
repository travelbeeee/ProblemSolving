#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, list[1000000];

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> list[i];

	vector<int> uniqueValue;
	for (int i = 0; i < N; i++)
		uniqueValue.push_back(list[i]);

	sort(uniqueValue.begin(), uniqueValue.end());
	uniqueValue.erase(unique(uniqueValue.begin(), uniqueValue.end()), uniqueValue.end());

	for (int i = 0; i < N; i++) {
		int left = 0, right = uniqueValue.size() - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (list[i] == uniqueValue[mid]) {
				cout << mid << ' ';
				break;
			}
			else if (list[i] < uniqueValue[mid]) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
	}
	return 0;
}
