#include<iostream>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N;
	int shortestDist[20][20];
	int dist[20][20] = {};

	cin >> N;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cin >> shortestDist[i][j];
			dist[i][j] = shortestDist[i][j];
		}
	}

	int ans = 0;
	bool impossible = false;
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == k || j == k || i == j) continue;
				// k번 째 노드를 거쳐서 갈 수 있으면 필요한 도로 X
				if (shortestDist[i][j] == 
					shortestDist[i][k] + shortestDist[k][j]) {
					dist[i][j] = 0;
				}
				// 입력된 최소거리가 잘못된 상태
				else if(shortestDist[i][j] >
					shortestDist[i][k] + shortestDist[k][j]){
					impossible = true;
				}
			}
		}
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			ans += dist[i][j];
	ans /= 2;

	if (impossible)
		ans = -1;
	cout << ans << '\n';

	return 0;

}
