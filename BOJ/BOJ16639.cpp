/*
	백트레킹

	괄호를 중첩해서, 아무곳에나 사용할 수 있음 
	--> 내 맘대로 계산하면된다!
	--> 백트레킹을 이용해 현재 숫자 쌍, 연산자 쌍을 넘겨주며 
	하나를 뽑아서 계산을 진행해나가면 된다.
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, ans = -2147483647;
string expressions;

void BT(vector<int> num, vector<char> op) {
	if (op.empty()) {
		ans = max(ans, num[0]);
		return;
	}

	for (int i = 0; i < op.size(); i++) {
		vector<int> cpNum = num;
		vector<char> cpOp = op;

		if (op[i] == '*')
			cpNum[i + 1] *= cpNum[i];
		else if (op[i] == '+')
			cpNum[i + 1] += cpNum[i];
		else
			cpNum[i + 1] = (cpNum[i] - cpNum[i + 1]);

		for (int j = i; j < num.size() - 1; j++)
			cpNum[j] = cpNum[j + 1];
		for (int j = i; j < op.size() - 1; j++)
			cpOp[j] = cpOp[j + 1];

		cpNum.pop_back();
		cpOp.pop_back();
		
		BT(cpNum, cpOp);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> expressions;

	vector<int> num;
	vector<char> op;

	for (int i = 0; i < N; i++){
		if (i % 2) op.push_back(expressions[i]);
		else num.push_back(expressions[i] - '0');
	}

	BT(num, op);

	cout << ans << '\n';

	return 0;
}
