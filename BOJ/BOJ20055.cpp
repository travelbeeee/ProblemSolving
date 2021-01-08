/*
	삼성기출답게 단순구현
	belt[i] := i번 째 벨트의 내구도
	conveyor[i] := 컨베이어 벨트의 i번 째 칸에 어떤 벨트가 있고, 로봇이 올라와있는지.
  
  1) conveyor 에서 벨트를 한 칸 씩 회전
  2) 컨베이어 벨트 위 로봇 이동 
  --> 마지막 벨트에 로봇이 있으면 일단 내리고 이동
  --> 로봇 이동 후 마지막 벨트에 또 로봇이 있으면 내린다.
  3) 컨베이어 벨트 첫 칸에 로봇 올리기
  4) 내구도가 끝난 벨트 
*/
#include<iostream>

using namespace std;

int N, K, belt[201];
pair<int, bool> conveyor[201]; // belt[i] := i번 째 컨베이어벨트가 몇 번 내구도이고 로봇이 있는지 없는지


int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;
	for (int i = 1; i <= 2 * N; i++)
		cin >> belt[i];
	for (int i = 1; i <= 2 * N; i++)
		conveyor[i] = { i, false };

	int time = 1;
	while (1) {
		// 벨트 한 칸 회전.
		pair<int, bool> temp = conveyor[2 * N];
		for (int i = 2 * N; i > 1; i--)
			conveyor[i] = conveyor[i - 1];
		conveyor[1] = temp;
		// 로봇 이동
		if (conveyor[N].second) conveyor[N].second = false;
		for (int i = N - 1; i >= 1; i--) {
			if (conveyor[i].second && !conveyor[i + 1].second && durability[conveyor[i + 1].first]) {
				belt[conveyor[i + 1].first]--;
				conveyor[i].second = false;
				conveyor[i + 1].second = true;
			}
		}
		if (conveyor[N].second) conveyor[N].second = false;
		// 로봇 올리기
		if (!conveyor[1].second && belt[conveyor[1].first]) {
			belt[conveyor[1].first]--;
			conveyor[1].second = true;
		}
		// 내구도가 0인 벨트 count
		int cnt = 0;
		for (int i = 1; i <= 2 * N; i++)
			if (belt[i] == 0) cnt++;

		if (cnt >= K) break;
		time++;
	}
	cout << time << '\n';
	return 0;
}
