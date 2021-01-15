/*
  DP - LIS(nlogn)
  
  경로 역추적을 위해 pair 배열 road를 추가.
  
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, A;
vector<int> v;
vector<pair<int, int>> road;
vector<int> ans;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;

	v.push_back(-1000000001);
	for (int i = 0; i < N; i++) {
		cin >> A;
		if (v.back() < A){
			road.push_back({ v.size() , A });
			v.push_back(A);
		}
		else {
			int index = lower_bound(v.begin(), v.end(), A) - v.begin();
			v[index] = A;
			road.push_back({ index, A });
		}
	}

	int idx = (int)v.size() - 1;
	for (int i = road.size() - 1; i >= 0; i--) {
		if (road[i].first == idx) {
			ans.push_back(road[i].second);
			idx--;
		}
	}

	cout << ans.size() << '\n';
	for (int i = ans.size() - 1; i >= 0; i--)
		cout << ans[i] << ' ';
	cout << '\n';

	return 0;
}
