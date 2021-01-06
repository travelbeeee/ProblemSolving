/*
	BFS탐색

	처음에는 그리디하게 앞 자리부터 뒤에서 제일 큰 숫자로 바꿔주고
	그 과정이 끝나고도 바꿔줘야하는 횟수가 남으면 맨 뒤 2개를 바꿔주는
	알고리즘을 생각
	--> 반례가 존재,,,,,, 
	값이 같은 숫자에 대해서 누구 먼저 앞으로 가져오냐에 따라 답이 달라지는 반례...

	--> 현재 어떤 값이고 교환 횟수가 몇 번 남았는지를 저장해가며 BFS탐색 진행.		
	--> 값은 1 ~ 1000000 중에 하나고 교환 횟수는 최대 10개 이므로
		BFS탐색을 하더라도 최대 10^6 * 10 의 경우의 수만 존재!
*/
#include<iostream>
#include<queue>
#include<string>

using namespace std;

int K, cnt = 0;
string N;
queue<pair<string, int>> q;
bool visited[1000001][11];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;

	q.push({ N, K });
	visited[stoi(N)][K] = true;

	while (!q.empty()) {
		string curS = q.front().first;
		int curK = q.front().second;
		q.pop();

		if (curK == 0)
			continue;

		for (int i = 0; i < (int)N.length(); i++) {
			for (int j = i + 1; j < (int)N.length(); j++) {
				string nextS = curS;
				char temp = nextS[i];
				nextS[i] = nextS[j];
				nextS[j] = temp;
				if (nextS[0] == '0') continue;
				if (visited[stoi(nextS)][curK - 1]) continue;

				q.push({ nextS, curK - 1 });
				visited[stoi(nextS)][curK - 1] = true;
			}
		}
	}

	int ans = 0;

	for (int i = 0; i < 1000001; i++)
		if (visited[i][0])
			ans = i;

	if ((int)N.length() == 1 || ((int)N.length() == 2 && N[1] == '0'))
		ans = -1;

	cout << ans << '\n';

	return 0;

}
