/*
  dp[i][j] := A의 (i - 1)번 째 글자, B의 (j - 1)번 째 글자에서 시작해서 A, B의 마지막 문자까지 봤을 때, 연속된 최대 문자열
  --> A[i - 1] != B[j - 1] 이면 dp[i][j] = 0;
  --> A[i - 1] == B[j - 1] 이면 dp[i][j] = 1 + dp[i + 1][j + 1];
  
  ex)
  ABRACADABRA
  ECADADABRBCRDARA
  
  dp[5][5] = (A문자열 "CADABRA" B문자열 "ADABRBCRDARA" 에서 앞에서부터 시작해 연속된 최대 문자열) = 0
  dp[6][5] = (A문자열 "ADABRA" B문자열 "ADABRBCRDARA" 애서 앞에서부터 시작해 연속된 최대 문자열) = "ADABR" = 5
*/

#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int N, M, dp[4002][4002] = {}, ans;
string A, B;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> A >> B;
	
	N = A.length(), M = B.length();

	for (int i = N; i > 0; i--)
		for (int j = M; j > 0; j--)
			if (A[i - 1] == B[j - 1]) {
				dp[i][j] = 1 + dp[i + 1][j + 1];
				ans = max(ans, dp[i][j]);
			}

	cout << ans << '\n';

	return 0;
}
