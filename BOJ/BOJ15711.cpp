/*
	A + B 가 짝수냐 홀수냐로 문제를 나눠서 해결하자
	1) A + B가 짝수
	 --> A + B 가 2라면 2개의 소수로 표현 불가
	 --> 골드바흐의 추측에 의해 2를 제외한 4조 이하의 짝수는 두 소수의 표현으로 가능함!
	2) A + B가 홀수
	 --> 홀수는 홀수 + 짝수의 합으로만 표현 가능
	 --> 짝수인 소수는 '2' 밖에없음
	 --> (A + B) - 2 가 소수이면 표현가능하고 아니면 불가능!
	 --> 이때, (A + B) - 2 가 최대 4 * 10^12 - 2 가 되므로
	     제곱근인 2 * 10^6 까지만 에라토스테네스체로 소수를 다 구해놓으면
		 최대크기의 Input이 들어와도 소수인지 아닌지 체크 할 수 있다.
*/

#include<iostream>
#include<vector>

using namespace std;

const int MAX_LENGTH = 2000000;
vector<int> prime;
bool eratos[MAX_LENGTH + 1];

void eratosthenes(void) { // 에라토스테네스체로 2백만 이하의 모든 소수를 구하자 false면 소수
	eratos[0] = eratos[1] = true;
	for (int i = 2; i <= MAX_LENGTH; i++) {
		if (eratos[i] == false) {
			prime.push_back(i);
			for (int j = i * 2; j <= MAX_LENGTH; j += i)
				eratos[j] = true;
		}
	}
}

bool isPrime(long long A) {
	if (A <= MAX_LENGTH) return !eratos[A];
	else{
		for (int i = 0; i < prime.size(); i++)
			if ( A % prime[i] == 0)
				return false;
		return true;
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	eratosthenes();

	int T;
	cin >> T;
	while (T--) {
		long long A, B, S;
		cin >> A >> B;
		S = A + B;
		if (S == 2) cout << "NO\n";
		else if (S % 2 == 0) cout << "YES\n"; // 골드바흐의추측
		else { // S가 홀수라면 --> 짝수 + 홀수 꼴만 가능 --> 짝수 소수는 2 밖에 없음
			if (isPrime(S - 2)) cout << "YES\n";
			else cout << "NO\n";
		}
	}
}
