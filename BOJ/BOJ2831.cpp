/*
	A : 키가 자기보다 작은 여자를 원하는 남자 그룹
	B : 키가 자기보다 큰 여자를 원하는 남자 그룹
	C : 키가 자기보다 작은 남자를 원하는 여자 그룹
	D : 키가 자기보다 큰 남자를 원하는 여자 그룹

	--> A, D / B, C 끼리만 매칭 가능!!

	A : 자기보다 작은 여자
	D : 자기보다 큰 남자
	--> 최대한 매칭시키려면 A그룹의 작은 남자를 D그룹의 작은 여자랑 매칭!

	B : 자기보다 큰 여자
	C : 자기보다 작은 남자
	--> 최대한 매칭시키려면, B그룹의 작은 남자를 C그룹의 작은 여자랑 매칭
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, height, ans = 0;
	vector<int> A, B, C, D;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> height;
		if (height > 0) A.push_back(-height);
		else B.push_back(height);
	}
	for (int i = 0; i < N; i++) {
		cin >> height;
		if (height > 0) C.push_back(-height);
		else D.push_back(height);
	}

	sort(A.begin(), A.end());
	sort(D.begin(), D.end());
	int i = 0, j = 0;
	while (i < A.size() && j < D.size()) {
		if (A[i] > D[j]) { // 매칭 성공
			ans++;
			i++, j++;
		}
		else { // 더 큰 남자를 찾아오자
			i++;
		}
	}


	sort(B.begin(), B.end());
	sort(C.begin(), C.end());
	i = 0, j = 0;
	while (i < B.size() && j < C.size()) {
		if (B[i] < C[j]) { // 매칭 성공
			ans++;
			i++, j++;
		}
		else { // 남자가 더 큼! --> 큰 여자를 찾자.
			j++;
		}
	}
	cout << ans << '\n';
}
