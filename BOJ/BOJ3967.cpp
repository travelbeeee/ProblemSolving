/*
  백트레킹
  
  'x' 자리에 'A' ~ 'L' 중 아직 안쓰인 알파벳을 하나씩 넣어보면 된다!
  --> 그냥 단순 백트레킹으로 진행하면 최악의 경우 O(12!)
  --> 시간초과!!
  
  [ 복잡도를 줄여보자 ]
  
  1) 정답은 1개는 존재하고, 사전 순으로 앞에 있는 걸 출력해야된다!
  --> 앞에서부터 'x'에 'A' ~ 'L' 중 아직 안쓰인 사전 순으로 가장 앞에 있는 알파벳을 넣어본다!
  --> 정답을 찾으면 해당 답이 사전 순으로 가장 앞에 있는 답이다
    --> backtracking에서 int s 를 파라미터로 넘겨주며 s 부터 탐색을 진행한다! ( 그 전은 탐색할 필요 X)
    --> ans 를 하나라도 찾으면 backtracking을 종료한다
    
  2) 6개의 Line 중에서 하나라도 완성된 줄이 있으면 26을 만족하는지 계속 체크한다.
  
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n;
string ans;
bool isUsed[12] = {};

int dx[12] = { 0, 1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 4 };
int dy[12] = { 4, 1, 3, 5, 7, 2, 6, 1, 3, 5, 7, 4 };

void print(string str) {
	int ind = 0;
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 9; j++)
			if (dx[ind] == i && dy[ind] == j)
				cout << str[ind++];
			else cout << '.';
		cout << '\n';
	}
}

bool checkSum(string str) {
	int sum[6] = {};
	int list[6][4] = {
		{0, 2, 5, 7},
		{0, 3, 6, 10},
		{1, 2, 3, 4},
		{7, 8, 9, 10},
		{1, 5, 8, 11},
		{4, 6, 9, 11}
	};
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++){
			if (str[list[i][j]] == 'x') {
				sum[i] = -1;
				break;
			}
			else
				sum[i] += (str[list[i][j]] - 'A') + 1;
		}
	}
	for (int i = 0; i < 6; i++)
		if (sum[i] != -1 && sum[i] != 26) return false;
	return true;
}

void backtracking(string str, int s, int cur, int goal) {
	if (ans != "") return;

	if (cur == goal) {
		if (checkSum(str))
			ans = str;
		return;
	}
	for (int i = s; i < 12; i++) {
		if (str[i] == 'x') {
			for (int j = 0; j < 12; j++) {
				if (!isUsed[j]) {
					str[i] = ('A' + j);
					isUsed[j] = true;
					if (checkSum(str))
						backtracking(str, i + 1, cur + 1, goal);
					isUsed[j] = false;
					str[i] = 'x';
				}
			}
			break;
		}
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	string map[5];
	for (int i = 0; i < 5; i++)
		cin >> map[i];

	int goal = 0;
	string str = "";
	for (int i = 0; i < 12; i++)
		str.push_back(map[dx[i]][dy[i]]);
	for (int i = 0; i < 12; i++){
		if (str[i] == 'x') goal++;
		else isUsed[(str[i] - 'A')] = true;
	}

	backtracking(str, 0, 0, goal);

	print(ans);

	return 0;
}
