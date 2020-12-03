/*
	구현

	진실을 아는 사람이 한 명이라도 있는 파티 --> 진실을 말해야됨 --> 전체 파티 참석자들이 진실을 알게됨.
	이때, 추가적으로 진실을 알게 된 사람들이 있는 파티 또한 같은 논리로 전체 파티 참석자들이 진실을 알게된다.
	
	따라서, 처음 입력된 진실을 아는 사람들에서 
	전체 파티를 순회하며 계속해서 진실을 아는 사람들을 늘려가야 된다.

	* 어떤 파티의 모든 참석자가 동일하게 진실을 알거나 혹은 진실을 모른다면 그 파티는 더 진행 X
	--> 모든 파티가 위의 조건을 만족한다면 더 이상 진실이 퍼져나가지 않으므로 루프를 깬다.
*/
#include<iostream>
#include<vector>

using namespace std;

int N, M, C;
bool liar[51];
vector<int> party[50];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> C;

	for (int i = 0, x; i < C; i++) {
		cin >> x;
		liar[x] = true;
	}

	for (int i = 0; i < M; i++) {
		cin >> C;
		for (int j = 0, x; j < C; j++) {
			cin >> x;
			party[i].push_back(x);
		}
	}
	// 각 파티를 순회하며 진실을 말해야하는 파티 체크
	while (1) {
		// 모든 파티의 파티원이 진실을 아는 사람만 있거나 진실을 모르는 사람만 있으면 됨.
		bool finished = true;
		for (int i = 0; i < M; i++) {
			bool check = liar[party[i][0]];
			for (int j = 1; j < party[i].size(); j++) {
				if (check != liar[party[i][j]])
					finished = false;
			}
		}

		if (finished) break;

		// 진실을 아는 사람이 있는 파티는 참가원들을 다 진실을 아는 사람으로 바꿔준다.
		for (int i = 0; i < M; i++) {
			bool isTruth = true;
			for (int j = 0; j < party[i].size(); j++)
				if (liar[party[i][j]]) isTruth = false;

			if (isTruth) continue;

			for (int j = 0; j < party[i].size(); j++)
				liar[party[i][j]] = true;
		}
	}

	int ans = 0;
	for (int i = 0; i < M; i++)
		if (!liar[party[i][0]]) ans++;

	cout << ans << '\n';

	return 0;
}
