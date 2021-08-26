/*
	준원이가 공격력이 낮은 순서대로 죽여가며 자신의 공격력을 올린다.
*/
#include<iostream>
#include<queue>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N;
	long long attack, A;
	priority_queue<long long> players;

	cin >> N;
	cin >> attack;
	for (int i = 0; i < N - 1; i++) {
		cin >> A;
		players.push(-A);
	}

	while (!players.empty() && attack > -players.top()) {
		attack += -players.top();
		players.pop();
	}

	if (players.empty()) cout << "Yes\n";
	else cout << "No\n";

	return 0;
}
