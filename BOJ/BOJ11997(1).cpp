/*
	브루트포스
	가능한 모든 경우의 x = a, y = b 선을 그려보면 된다.
	
	소들의 좌표 중 X좌표 Y좌표를 따로 생각해보자.
	erase, unique 함수를 통해 중복된 X좌표, Y좌표 값들을 다 날렸다 가정하자.
	좌표는 다 양의 홀수이므로 중복된 좌표가 없다면 모두 1 이상 차이가 난다.
	따라서, 사이사이의 모든 값들에 대해서 선을 그려보면 된다.

	  V    V     V    V     V ( V표시된 곳에서 x = a )
	   X[0]  X[1] ...   X[K]

	  V    V     V    V     V ( V표시된 곳에서 y = b )
	   Y[0]  Y[1] ...   Y[T]
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, ans = 1000;
pair<int, int> point[1000];
vector<int> X, Y;

int getAnswer(int x, int y) {
	int cnt[4] = {};
	for (int i = 0; i < N; i++) {
		if (point[i].first > x && point[i].second > y) cnt[0]++;
		else if (point[i].first > x && point[i].second < y) cnt[1]++;
		else if (point[i].first < x && point[i].second > y) cnt[2]++;
		else cnt[3]++;
	}
	int M = 0;
	for (int i = 0; i < 4; i++)
		M = max(M, cnt[i]);
	return M;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> point[i].first >> point[i].second;
		X.push_back(point[i].first), Y.push_back(point[i].second);
	}

	X.push_back(-1);
	Y.push_back(-1);

	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());

	X.erase(unique(X.begin(), X.end()), X.end());
	Y.erase(unique(Y.begin(), Y.end()), Y.end());

	for (int i = 0; i < (int)X.size(); i++)
		for (int j = 0; j < (int)Y.size(); j++){
			ans = min(ans, getAnswer(X[i] + 1, Y[j] + 1));
		}

	cout << ans << '\n';

	return 0;
}
