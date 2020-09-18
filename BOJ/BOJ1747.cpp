/*
	어떤 수 N이 들어오면 N부더 시작해서 숫자를 키워가며 소수인지, 펠린드롬인지 체크한다.

	1) 소수인지 체크
	: 에라토스테네스 체를 이용해서 미리 1000,0000 까지 소수를 다 구해둔다.
	--> 입력 최대인 100,0000 이 들어왔을 때 100,3001 이 정답이므로 1000만이 아니라 110만 까지만 구해놨어도 충분...!!

	2) 펠린드롬인지 체크
	: 숫자 x를 각 자리마다 뽑아서 vector 에 담아두고 앞 뒤가 같은지 체크한다.
*/

#include<iostream>
#include<vector>

using namespace std;

bool isPrime[10000001];

void eratos() {
	isPrime[0] = isPrime[1] = true;
	for (int i = 2; i <= 10000000; i++) {
		if (!isPrime[i]) {
			for (int j = 2 * i; j <= 10000000; j += i)
				isPrime[j] = true;
		}
	}
}

bool isPalindrome(int x) {
	vector<int> numbers;
	while (x) {
		numbers.push_back(x % 10);
		x /= 10;
	}
	bool ans = true;
	for (int i = 0; i < ((int)numbers.size() / 2); i++) {
		if (numbers[i] != numbers[numbers.size() - 1 - i]) ans = false;
	}
	return ans;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	eratos();
	int N, x;
	cin >> N;

	x = N;
	while (1) {
		if (!isPrime[x] && isPalindrome(x)){
			cout << x << '\n';
			break;
		}
		x++;
	}
	return 0;
}
