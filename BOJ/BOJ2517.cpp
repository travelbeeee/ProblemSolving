#include<iostream>
#include<vector>
#include<algorithm>
#define ll long long

using namespace std;

const int N_MAX = 500000;
int ab[N_MAX];
vector<int> sortedAb;
ll tree[4 * N_MAX];

ll sum(int index, int start, int end, int left, int right) {
	if (end < left || right < start)
		return 0;
	if (left <= start && end <= right)
		return tree[index];
	int mid = (start + end) / 2;
	return sum(2 * index + 1, start, mid, left, right) + sum(2 * index + 2, mid + 1, end, left, right);
}

ll update(int index, int start, int end, int changed, int diff) {
	if (changed < start || end < changed) return tree[index];
	if (start == end) return tree[index] = diff;
	int mid = (start + end) / 2;
	return tree[index] = update(index * 2 + 1, start, mid, changed, diff) + update(index * 2 + 2, mid + 1, end, changed, diff);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> ab[i];
		sortedAb.push_back(ab[i]);
	}
	sort(sortedAb.begin(), sortedAb.end());

	for (int i = 0; i < N; i++) {
		int ind = (lower_bound(sortedAb.begin(), sortedAb.end(), ab[i]) - sortedAb.begin());
		update(0, 0, N - 1, ind, 1);
		cout << (i + 1) - sum(0, 0, N - 1, 0, ind - 1) << '\n';
	}
	return 0;
}
