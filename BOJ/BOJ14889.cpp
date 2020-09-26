/*
	백트레킹을 이용해 N명의 선수 중 (N / 2) 명을 뽑아서 A팀으로 선정.
	뽑히지 않은 나머지 선수를 뽑아서 B팀으로 선정.

	A팀, B팀의 score를 각각 계산해 차이값을 답에 갱신
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int N, ability[20][20], ans = 99999999;

int getScore(vector<int> player) {
	int score = 0;
	for (int i = 0; i < player.size(); i++) {
		for (int j = i + 1; j < player.size(); j++) {
			score += ability[player[i]][player[j]];
			score += ability[player[j]][player[i]];
		}
	}
	return score;
}

void backtracking(vector<int> player, int s) {
	if (player.size() == (N / 2)) {
		// player에 있는 애들이랑 아닌 애들로 나뉨.
		bool selectedPlayer[20] = {};
		for (int i = 0; i < player.size(); i++)
			selectedPlayer[player[i]] = true;
		
		vector<int> newPlayer;
		for (int i = 0; i < N; i++)
			if (!selectedPlayer[i]) newPlayer.push_back(i);

		int scoreA = getScore(player), scoreB = getScore(newPlayer);
		ans = min(ans, abs(scoreA - scoreB));
		return;
	}
	for (int i = s; i < N; i++) {
		player.push_back(i);
		backtracking(player, i + 1);
		player.pop_back();
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> ability[i][j];

	vector<int> v;
	backtracking(v, 0);

	cout << ans << '\n';
}
