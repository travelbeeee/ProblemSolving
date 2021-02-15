/*
	브루트포스

	낮에는 어차피 죽여야되는 사람이 무조건 고정!
	--> 밤에만 마피아가 죽일 사람을 고르면서 경우의 수 발생
	--> N이 최대여도 모든 경우의수는 15 * 13 * 11 * 9 * 7 * 5 * 3 으로 크지 않음
	--> 마피아가 죽일 수 있는 모든 사람들을 죽여가며 게임을 진행해보자.
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, S, ans;
int R[16][16];
const int INF = 99999;

void doGame(int curN, vector<int> guiltiness, int day) {
	if (curN % 2) { // 낮
		// 가장 유죄 점수가 크면서 번호가 낮은 사람을 찾자.
		int ind = 0, maxGuiltiness = -INF;
		for (int i = 0; i < N; i++) {
			if (maxGuiltiness < guiltiness[i]) {
				ind = i, maxGuiltiness = guiltiness[i];
			}
		}
		// 마피아 밖에 안남거나 마피아가 죽어서 게임 끝
		if (ind == S) {
			ans = max(ans, day);
			return;
		}
		// 죽은 사람 유죄 점수 처리
		guiltiness[ind] = -INF;
		doGame(N - 1, guiltiness, day);
	}
	else { // 밤
		for (int i = 0; i < N; i++) {
			if (guiltiness[i] == -INF) continue; // 이미 죽은 사람
			if (i == S) continue; // 마피아 본인 자신
			
			// i 를 죽임
			int temp = guiltiness[i];
			for (int j = 0; j < N; j++){
				if (guiltiness[j] == -INF) continue;
				guiltiness[j] += R[i][j];
			}
			guiltiness[i] = -INF;
			doGame(N - 1, guiltiness, day + 1);
			for (int j = 0; j < N; j++){
				if (guiltiness[j] == -INF) continue;
				guiltiness[j] -= R[i][j];
			}
			guiltiness[i] = temp;
		}
	}

	return;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	vector<int> guiltiness(N);
	for (int i = 0; i < N; i++)
		cin >> guiltiness[i];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> R[i][j];
	cin >> S;

	doGame(N, guiltiness, 0);

	cout << ans << '\n';

	return 0;
}
