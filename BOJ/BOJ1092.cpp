/*
	1) 제일 쎈 크레인이 제일 무거운 박스를 나를 수 없다면 -1

	2) 쎈 크레인부터 나를 수 있는 제일 무거운 박스 중 아직 나르지 않은 박스를 나른다.

	이때, 크레인이 나를 수 있는 가장 무거운 박스를 매번 탐색해서 찾는다면 시간초과가 발생하므로
	정렬 후, pointer[i] := i번 째 크레인이 나를 수 있는 가장 무거운 박스를 저장해놓는다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, M;
	int crane[50], box[10000];

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> crane[i];
	cin >> M;
	for (int i = 0; i < M; i++)
		cin >> box[i];

	sort(crane, crane + N);
	sort(box, box + M);

	if (crane[N - 1] < box[M - 1]) {
		cout << -1 << '\n';
		return 0;
	}

	int pointer[50];
	for (int i = 0; i < N; i++) pointer[i] = -1;

	int cInd = 0, bInd = 0;
	while (cInd < N && bInd < M) {
		if (crane[cInd] < box[bInd]) {
			if (cInd + 1 < N) pointer[cInd + 1] = pointer[cInd];
			cInd++;
		}
		else {
			pointer[cInd] = bInd;
			bInd++;
		}
	}
	while (cInd + 1 < N) {
		pointer[cInd + 1] = pointer[cInd];
		cInd++;
	}

	int ans = 0, visitedCnt = 0;
	bool visited[10000] = {};
	while (visitedCnt < M) {
		for (int i = N - 1; i >= 0; i--) {
			while (0 <= pointer[i] && visited[pointer[i]]) {
				pointer[i]--;
			}
			if (0 <= pointer[i]) {
				visited[pointer[i]] = true;
				visitedCnt++;
			}
		}
		ans++;
	}

	cout << ans << '\n';

	return 0;
}
