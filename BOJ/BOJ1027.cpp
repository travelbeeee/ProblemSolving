/*
	i번 째 빌딩에서 j번 째 빌딩을 볼 수 있는가
	--> i 와 j 빌딩 사이에 있는 모든 빌딩들이 (i, buildings[i]) (j, buildings[j]) 직선 아래에 있으면 됨.
	--> (i, b[i]), (j, b[j]) 를 지나는 직선의 방정식에 i 와 j 빌딩 사이에 있는 모든 빌딩의 x 좌표값을 대입해 얻은 y 값과 실제 빌딩의 높이를 비교해본다.
*/

#include<iostream>
#include<algorithm>

using namespace std;

int N, ans;
long long buildings[51];

bool checkPossible(int i, int j) {
	int left = min(i, j), right = max(i, j);
	for (int k = left + 1; k < right; k++) // left와 right 사이에 있는 애들
		if (1LL * (right - left) * buildings[k] >= 1LL * (buildings[right] - buildings[left]) * (k - left) + 1LL * (right - left) * buildings[left]) 
			return false;
	return true;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> buildings[i];

	for (int i = 1; i <= N; i++) { // i번 째 건물부터
		int cnt = 0;
		bool check = true;
		// i 건물이랑 j 건물이 보이는지 체크하자.
		for (int j = 1; j <= N; j++) {
			if (i == j) continue;
			if (checkPossible(i, j)) cnt++;
		}
		ans = max(ans, cnt);
	}
	cout << ans << '\n';
	return 0;
}
