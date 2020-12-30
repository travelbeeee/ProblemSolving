/*
	Map Union-find

	자료구조 Map을 이용해서 나라이름마다 번호를 Mapping 해주고,
	이를 Union-find 를 이용해 속국-종주국 관계를 정해주면 된다.

	이때, 속국-종주국 관계가 바뀌는 경우만 merge2 함수를 이용해서 처리해주면 된다.

*/
#include<iostream>
#include<map>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

int N, M, p[500];
map<string, int> m;
vector<string> ans;

string input1, input2, input3, input4, input5;
string kingdom1, kingdom2;
char op;

int find(int cur) {
	if (p[cur] < 0) return cur;
	return p[cur] = find(p[cur]);
}

void merge(int x, int y) { 
	int pX = find(x), pY = find(y);
	p[pX] += p[pY];
	p[pY] = pX;
	return;
}

void merge2(int x, int y) {
	if (p[y] >= 0)
		return;
	else {
		p[x] = p[y];
		p[y] = x;
	}
}

int main(void) {
	ios::sync_with_stdio(false);

	cin >> N >> M;

	for (int i = 0; i < N; i++)
		p[i] = -1;

	for (int i = 0; i < N; i++) {
		cin >> input1 >> input2 >> kingdom1;
		m.insert({ kingdom1, i });
	}

	for (int i = 0; i < M; i++) {
		cin >> input1 >> input2 >> input3 >> input4 >> input5;
		kingdom1 = input3.substr(0, (int)input3.length() - 8);
		kingdom2 = input5.substr(0, (int)input5.length() - 2);
		op = input5[(int)input5.length() - 1];
		
		if (op == '1') { // kingdom2 가 kingdom1 에게 먹힘
			if (find(m[kingdom1]) == find(m[kingdom2]))
				merge2(m[kingdom1], m[kingdom2]);
			else
				merge(m[kingdom1], m[kingdom2]);
		}
		else {
			if (find(m[kingdom1]) == find(m[kingdom2]))
				merge2(m[kingdom2], m[kingdom1]);
			else
				merge(m[kingdom2], m[kingdom1]);
		}
	}

	map<string, int>::iterator iter;
	for (iter = m.begin(); iter != m.end(); iter++) {
		if (p[iter->second] < 0) ans.push_back(iter->first);
	}
	
	sort(ans.begin(), ans.end());

	cout << ans.size() << '\n';
	for (int i = 0; i < ans.size(); i++) {
		cout << "Kingdom of " << ans[i] << '\n';
	}
}
