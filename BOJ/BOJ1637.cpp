/*
	BinarySearch 수학

	정수더미 안에 있는 숫자가 몇 개 있는지 신경쓰지말고,
	서로 다른 T개의 숫자가 있다고 해보자.
	(n1, n2, n3, ... nT)

	문제 조건에 의하면 
	T개의 숫자들은 모두 짝수개로 존재하거나
	하나만 홀수개이고 나머지는 짝수개로 존재한다.

	f(x) := x보다 작거나 같은 정수더미의 숫자들의 갯수
	로 정의하면 f(x) 는 짝수이지만, f(x + 1) 은 홀수인 구간이 
	문제 조건에 의해 생긴다.
	이 x를 찾으면 된다.

*/
#include<iostream>
#include<tuple>
#include<algorithm>

using namespace std;

typedef long long ll;

ll N, ans = -1, ansCnt, A, B, C;
tuple<ll, ll, ll> list[20000];

ll getCnt(ll mid) {
	ll cnt = 0;
	for (int i = 0; i < N; i++) {
		if (mid < get<0>(list[i])) continue;
		cnt += ((min(mid, get<2>(list[i])) - get<0>(list[i])) / get<1>(list[i])) + 1;
	}
	return cnt;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A >> C >> B;
		list[i] = make_tuple(A, B, C);
	}

	ll left = 1, right = 2147483647;
	while (left <= right) {
		ll mid = (left + right) / 2 ;
		ll cnt = getCnt(mid);
		if (cnt % 2) {
			right = mid - 1;
			ans = mid;
		}
		else {
			left = mid + 1;
		}
	}
	
	if (ans == -1) cout << "NOTHING\n";
	else cout << ans << ' ' << getCnt(ans) - getCnt(ans - 1) << '\n';

	return 0;
}
