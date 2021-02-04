/*
	완전 K진 트리이므로
	현재 노드의 부모노드는 (현재노드 - 2) / K + 1 로 추적가능
	
	따라서, 시간 복잡도는 다음과 같다.
	밑이 k인 log로 O(Q * logN)

	--> K가 1인 경우만 따로 처리해주자!
*/
#include<iostream>
#include<cmath>

using namespace std;
using ll = long long;

ll N, K, Q, x, y;

ll getDist(ll x, ll y) {
	if (K == 1)
		return abs(x - y);

	ll dist = 0;
	while (x != y) {
		if (x > y) {
			x = ((x - 2) / K) + 1;
			dist++;
		}
		else {
			y = ((y - 2) / K) + 1;
			dist++;
		}
	}
	return dist;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> x >> y;
		cout << getDist(x, y) << '\n';
	}
	
	return 0;
}
