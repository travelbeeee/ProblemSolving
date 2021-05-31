/*
	t초에서 k층 막대기가 어디부터 어디까지 있는지 알아내자!
	전체길이 L, 막대기길이 len
	
	M = L - len ( M이 0이면 그냥 전체 범위 )
	1) d = 0인 경우
		1-1) (t / M)이 짝수 --> 오른쪽으로 이동 중
			(t % M) ~ (t % M  + len) 까지가 막대기 범위
		1-2) (t / M)이 홀수 --> 왼쪽으로 이동 중
			(L - len) - (t % M) ~ L - (t % M)

	2) d = 1인 경우
		1-1) (t / M)이 홀수 --> 오른쪽으로 이동 중
			(L - len) - (t % M) ~ L - (t % M)
		1-2) (t / M)이 짝수 --> 왼쪽으로 이동 중
			(t % M) ~ (t % M + len)
*/
#include<iostream>
#include "소스.h"

using namespace std;

int N, L;
int len[3000], d[3000];

pair<int, int> getBarRange(int curFloor, int time) {
	int M = L - len[curFloor];
	if (M == 0) return { 0, L };

	if (!(d[curFloor] % 2) && !((time / M) % 2))
		return { time % M, time % M + len[curFloor] };
	if (d[curFloor] % 2 &&(time / M) % 2)
		return { time % M, time % M + len[curFloor] };
	return { L - len[curFloor] - (time % M), L - (time % M) };
}

bool isRangeOverLap(pair<int, int> barA, pair<int, int> barB) {
	if (barA.second < barB.first) return false;
	if (barB.second < barA.first) return false;
	return true;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> L;
	for (int i = 0; i < N; i++)
		cin >> len[i] >> d[i];

	int t = 0, floor = 0;
	while (floor < N) {
		while (floor + 1 < N) {
			pair<int, int> barRange = getBarRange(floor, t);
			pair<int, int> nextBarRange = getBarRange(floor + 1, t);
			if (isRangeOverLap(barRange, nextBarRange))
				floor++;
			else
				break;
		}
		if (floor == N - 1) break; // 끝에 도착
		t++;
	}
	cout << t << '\n';
	return 0;
}
