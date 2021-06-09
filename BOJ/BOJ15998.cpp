/*
* 1) 입금 상황
* --> 입금 후 잔고가 맞게 나와있는지 확인한다
* 
* 2) 출금 상황
*	2-1) 추가로 충전할 필요가 없는 상황
*		--> 출금 후 잔고가 맞게 나와있는지 확인한다
*	
*	2-2) M단위로 추가 충전이 필요한 상황
*		현재 잔고가 c원, a원을 출금하고 b원이 잔고로 남는다고 가정하자.
*		그러면 우리는 (a - c) 원 만큼 잔고가 부족한 상황이고 b원이 남아야되므로
*		총 (a - c) + b 원 만큼 M 단위로 충전이 되야한다.
*		--> (a - c) + b 는 M의 배수여야된다.
*		--> 또, b원이 남아야되므로 M은 b보다 커야한다.
*		--> M은 (a - c) + b의 약수 중 b보다 큰 값이여야한다.
*		따라서, 이런 상황들을 모두 모아 최대공약수를 구하고,
*		최대공약수가 b 보다 큰 값이고 범위 안에 들어오는 값이면 M이 존재하고, 아니면 불가능한 상황이다.
* 
*	Tip) 입금 혹은 출금이 정상적으로 이루어지는 경우에도 로그를 확인해줘야한다.
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define ll long long

const ll MAX = 9000000000000000000;

int N;
vector<pair<ll, ll>> logs;
ll a, b;

ll GCD(ll a, ll b) {
	while (b) {
		ll r = a % b;
		a = b;
		b = r;
	}
	return a;
}

ll makeGCD(vector<ll> divide) {
	ll res = divide[0];
	for (int i = 1; i < divide.size(); i++)
		res = GCD(res, divide[i]);
	return res;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		logs.push_back({ a, b });
	}

	int isPossible = 1;
	ll maxValue = -1, balance = 0;
	vector<ll> divide;
	for (pair<ll, ll> log : logs) {
		if (log.first > 0 || -log.first <= balance) { // 입금 혹은 출금이 정상적으로 이루어지는 경우
			balance += log.first;
			if (balance != log.second){
				isPossible = -1;
				break;
			}
		}
		else { // 출금 충전필요
			divide.push_back(log.second - (balance + log.first));
			maxValue = max(maxValue, log.second);
			balance = log.second;
		}
	}

	if (maxValue == -1) cout << isPossible << '\n';
	else {
		ll gcd = makeGCD(divide);
		if (maxValue < gcd && gcd <= MAX) {
			cout << gcd << '\n';
		}
		else
			cout << -1 << '\n';
	}
	
	return 0;
}
