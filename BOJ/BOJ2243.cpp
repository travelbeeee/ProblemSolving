/*
	K순위의 사탕을 어떻게 찾을것인가??

	K순위의 사탕의 맛이 M이라고 할 때,
	맛1 ~ 맛M까지 사탕의 합이 K가 된다.
	--> 세그먼트트리를 이용하자!
	또, 맛 M을 이분탐색을 이용해서 찾자.
*/
#include<iostream>
#include<algorithm>
using namespace std;

int n, A, B, C;
int tree[4 * 1000001];

int getSum(int index, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	else if (left <= start && right >= end) return tree[index];

	int mid = (start + end) / 2;
	return getSum(index * 2 + 1, start, mid, left, right) +
		getSum(index * 2 + 2, mid + 1, end, left, right);
}

void update(int index, int start, int end, int changed_index, int diff){
	if (changed_index < start || changed_index > end)
		return;

	tree[index] += diff;

	if (start != end) {
		int mid = (start + end) / 2;
		update(index * 2 + 1, start, mid, changed_index, diff);
		update(index * 2 + 2, mid + 1, end, changed_index, diff);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> A;
		if (A == 1) { // 사탕 꺼내기
			cin >> B;
			int left = 1, right = 1000000, value = 1000000;
			while (left <= right) {
				int mid = (left + right) / 2;
				int sum = getSum(0, 0, 1000000, 0, mid);
				if (B <= sum) {
					value = min(mid, value);
					right = mid - 1;
				}
				else {
					left = mid + 1;
				}
			}
			cout << value << '\n';
			update(0, 0, 1000000, value, -1);
		}
		else { // 사탕 넣기
			cin >> B >> C;
			update(0, 0, 1000000, B, C);
		}
	}
}
