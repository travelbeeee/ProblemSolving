/*
  투포인터
  1) 동물의 (x, y) 좌표를 (x + L - y, x + L + y) 로 바꿔서 해당 동물을 잡을 수 있는 사냥꾼의 위치 범위를 담는다
  2) 사냥꾼과 동물의 범위를 오름차순으로 sorting 한다.
  3) 사냥꾼과 동물을 잡을 수 있는 사냥꾼의 위치 범위를 투 포인터로 순회하며
    3-1) 해당 동물의 범위에 사냥꾼이 해당 --> 동물을 잡음 count
    3-2) 해당 동물의 범위가 사냥꾼보다 왼쪽에 있으면 --> 다음 동물을 순회한다.
    3-3) 해당 동물의 범위가 사냥꾼보다 오른쪽에 있으면 --> 다음 사냥꾼으로 사냥꾼을 바꾼다.
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, M, L;
	vector<int> hunter(100000);
	vector<pair<int, int>> animal(100000);
	vector<pair<int, int>> animalX;

	cin >> M >> N >> L;
	for (int i = 0; i < M; i++) {
		cin >> hunter[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> animal[i].first >> animal[i].second;
	}
	for (int i = 0; i < N; i++) {
		if (animal[i].second > L) continue;
		animalX.push_back({ animal[i].first - (L - animal[i].second),
			animal[i].first + (L - animal[i].second) });
	}
	N = animalX.size();

	sort(hunter.begin(), hunter.begin() + M);
	sort(animalX.begin(), animalX.end());

	int hInd = 0, aInd = 0, ans = 0;
	while (hInd < M && aInd < N) {
		if (animalX[aInd].first <= hunter[hInd]
			&& hunter[hInd] <= animalX[aInd].second) {
			ans++;
			aInd++;
		}
		else if (animalX[aInd].second < hunter[hInd]) {
			aInd++;
		}
		else if (hunter[hInd] < animalX[aInd].first) {
			hInd++;
		}
	}
	cout << ans << '\n';
	return 0;
}
