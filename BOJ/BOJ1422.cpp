/*
	2가지를 기준으로 Sorting 을 진행하면된다.

	1) 우리는 K개의 숫자를 무조건 한 번 씩은 사용해야된다.
	--> cmp1 을 이용
	K개의 숫자를 한 번 씩 사용할거므로 결과적으로 숫자의 자릿수는 다 똑같다.
	--> 숫자 A, B 가 있을 때 AB / BA 를 비교해서 앞에 붙이면 
	    더 좋은 숫자들 순으로 정렬한다.

	2) 우리는 (N - K)개의 숫자는 중복해서 뽑아야된다.
	--> cmp2 을 이용
	중복해서 뽑을 때는 1) 의 기준과는 다르게 자릿수에 영향을 받는다.
	--> 자릿수가 더 큰 숫자에게 높은 우선 순위를 주고,
		같다면 값이 더 큰 숫자에게 높은 우선 순위를 준다.

	==> 우리가 사용할 숫자 N개는 
	cmp2로 정렬한 후 가장 우선 순위가 높은 수를 (N -K)번 뽑고,
	나머지 숫자들을 다 한 번 씩 뽑은 숫자다.
	
	==> 숫자 N개를 cmp1으로 정렬하고 앞에서부터 출력하면 정답이 된다.
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int K, N;
string list[1000];
vector<string> ans;

bool cmp1(string A, string B) {
	string C = A + B;
	string D = B + A;
	for (int i = 0; i < C.length(); i++)
		if (C[i] > D[i]) return true;
		else if (C[i] < D[i]) return false;
	return false;
}

bool cmp2(string A, string B) {
	if ((int)A.length() == (int)B.length()) {
		for (int i = 0; i < A.length(); i++)
			if (A[i] > B[i]) return true;
			else if (A[i] < B[i]) return false;
	}
	return ((int)A.length() > (int)B.length());
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> K >> N;
	for (int i = 0; i < K; i++) {
		cin >> list[i];
	}
	
	sort(list, list + K, cmp2);

	for (int i = 0; i < (N - K); i++)
		ans.push_back(list[0]);
	for (int i = 0; i < K; i++)
		ans.push_back(list[i]);

	sort(ans.begin(), ans.end(), cmp1);

	for (int i = 0; i < N; i++)
		cout << ans[i]; 

	return 0;
}
