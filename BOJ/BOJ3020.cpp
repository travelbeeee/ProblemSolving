/*
	# 메모리제이션을 이용해서 복잡도를 낮출 수 있는 문제
  
	up[i] := 길이가 i인 바닥에서 시작하는 장애물의 개수
	down[i] := 길이가 i인 천장에서 시작하는 장애물의 개수
	
	--> sumUp[i] := 바닥을 기준으로 i번 째 구간으로 이동할 때 부수는 장애물의 개수
				:= up[i] + sumUp[i + 1];
	--> sumDown[i] := 천장을 기준으로 i번 째 구간으로 이동할 때 부수는 장애물의 개수
				:= down[i] + sumDown[i + 1];

	--> 우리가 바닥을 기준으로 i번 째 구간에서 이동한다고 가정하면
		sumUp[i] + sumDown[(H + 1) - i] 만큼의 장애물을 부수게 된다.

*/
#include<iostream>

using namespace std;

int N, H;
int up[500002];
int down[500002];
int sumUp[500002];
int sumDown[500002];
int ansObs = 9999999, ansCnt;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> H;
	for (int i = 0, x, y; i < N / 2; i++) {
		cin >> x >> y;
		up[x]++, down[y]++;
	}
	for (int i = H; i > 0; i--) {
		sumUp[i] = up[i] + sumUp[i + 1];
		sumDown[i] = down[i] + sumDown[i + 1];
	}
	// 각 구간마다 이동해보자!
	for (int i = 1; i <= H; i++) {
		int obs = sumUp[i] + sumDown[H - i + 1];
		if (obs < ansObs) {
			ansObs = obs;
			ansCnt = 1;
		}
		else if (obs == ansObs) {
			ansCnt++;
		}
	}
	cout << ansObs << ' ' << ansCnt << '\n';

	return 0;

}
