/*
	Dp[i][j] := f(i) 를 2^j 만큼 계산한 값
	ex) Dp[1][2] = f(1) 을 4번 계산한 값 = f(f(f(f(1))))

	--> Dp[i][j] = Dp[Dp[i][j - 1]][j - 1] 이 성립한다.
	
	Dp 배열을 통해 f(x) 를 2^n 번 연산한 값들을 미리 구해놓을 수 있다.

	--> N과 X가 주어지면 f(X)를 N번 연산해서 결과를 출력해줘야한다.
	--> N을 2진수로 표현한다음에 Dp배열 값을 이용하면 된다.
*/
#include<iostream>
#include<cmath>

using namespace std;

int n, m, Q, x;
int dp[200001][19];

void setDp(void) {
	for (int j = 1; j < 19; j++) {
		for (int i = 1; i <= n; i++) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
	}
	return;
}


int calFunc(int N, int X) {
	int idx = 0, res = X;
	while (N) {
		if (N % 2) {
			res = dp[res][idx];
		}
		idx++;
		N /= 2;
	}
	return res;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> dp[i][0];
	
	setDp();
	
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> n >> x;
		cout << calFunc(n, x) << '\n';
	}

	return 0;
}
