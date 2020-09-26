/*
	# 백트레킹 이용
	주어진 덧셈,뺄셈,곱셈,나눗셈 기호에서 만들 수 있는 모든 순서쌍을 만들어본다.
	그 후, 계산해서 정답 갱신
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N, minAns = 1000000000, maxAns = -1000000000;
int numbers[11], op[4];

int getScore(vector<int> operations) {
	int score = numbers[0];

	for (int i = 0; i < N - 1; i++) {
		if (operations[i] == 0) // 덧셈
			score += numbers[i + 1];
		else if (operations[i] == 1) // 뺼셈
			score -= numbers[i + 1];
		else if (operations[i] == 2)
			score *= numbers[i + 1];
		else
			score /= numbers[i + 1];
	}

	return score;
}
void backtracking(vector<int> operations) {
	if (operations.size() == N - 1) {
		minAns = min(minAns, getScore(operations));
		maxAns = max(maxAns, getScore(operations));
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (op[i]) {
			operations.push_back(i);
			op[i]--;
			backtracking(operations);
			op[i]++;
			operations.pop_back();
		}
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> numbers[i];

	for (int i = 0; i < 4; i++)
		cin >> op[i];

	vector<int> v;
	backtracking(v);

	cout << maxAns << '\n' << minAns << '\n';

	return 0;
}
