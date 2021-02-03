/*
	0번 사람부터 순회하며 가지고 있는 블록을 사용하여 새로운 블록을 만든다.

	j 크기로 기존에 만든 블록이 있다.
	--> j 크기 + 내가 가지고 있는 블록 을 통해 새로운 블록 형성
	
	0 크기의 블록이 존재한다고 dp[0] = 1을 설정해서
	내가 가지고 있는 블록만을 이용해서 블록을 만드는 경우도 한 번에 처리하자.
*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;

const int m = 10007;
int N, M, H;
int dp[1001];
vector<int> blocks[50];
string input;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> M >> H;

	cin.ignore(1);
	for (int i = 0; i < N; i++) {
		getline(cin, input);
		int ind = 0;
		string n = "";
		while (ind < input.size()) {
			while ('0' <= input[ind] && input[ind] <= '9') {
				n += input[ind];
				ind++;
			}
			blocks[i].push_back(stoi(n));
			n = "";
			ind++;
		}
	}

	dp[0] = 1;
	for (int i = 0; i < N; i++) {
		// 먼저 기존에 쌓여온 블록 + 가지고 있는 블록 추가
		int tempDp[1001] = {};
		for (int j = 0; j <= H; j++) 
			if (dp[j]) // j크기만큼 블록을 쌓은 경우가 존재.
				for (int k = 0; k < blocks[i].size(); k++)
					if (j + blocks[i][k] <= H) // 가지고 있는 블록 추가
						tempDp[j + blocks[i][k]] += dp[j];

		for (int j = 0; j <= H; j++) 
			dp[j] = (dp[j] + tempDp[j]) % m;
	}

	cout << dp[H] << '\n';

	return 0;
}
