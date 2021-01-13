/*
	구현

	Slump, Slimp, Slurpy 를 문제에 조건에 맞춰서
	재귀적으로 검증해주면 된다.

*/
#include<iostream>

using namespace std;

bool checkSlump(string str) {
	if ((int)str.length() < 3) return false;
	if (!(str[0] == 'D' || str[0] == 'E')) return false;
	if (str[1] != 'F') return false;

	int idx = 1;
	while (idx < (int)str.length() && str[idx] == 'F')
		idx++;
	// F로 끝남.
	if (idx == (int)str.length()) return false;
	
	// F반복 끝에 G가 오고 마지막임 --> Slump
	if (str[idx] == 'G' && idx == (int)str.length() - 1) 
		return true;

	if (checkSlump(str.substr(idx, (int)str.length() - idx))) 
		return true;

	return false;
}

bool checkSlimp(string str) {
	if (str.length() < 2) return false;
	if (str[0] != 'A') return false;
	if ((int)str.length() == 2 && str[1] != 'H') return false;
	if ((int)str.length() == 2 && str[1] == 'H') return true;

	if (str[1] == 'B' && str[(int)str.length() - 1] == 'C'&&
		checkSlimp(str.substr(2, (int)str.length() - 3)))
			return true;

	if (str[1] != 'B' && str[(int)str.length() - 1] == 'C' && 
		checkSlump(str.substr(1, (int)str.length() - 2 )))
			return true;
	return false;
}

bool checkSlurpy(string str) {
	for (int i = 2; i < (int)str.length(); i++) {
		if (checkSlimp(str.substr(0, i)) && checkSlump(str.substr(i, (int)str.length() - i)))
			return true;
	}
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N;
	string str;

	cin >> N;

	cout << "SLURPYS OUTPUT\n";
	for (int i = 0; i < N; i++) {
		cin >> str;
		if (checkSlurpy(str)) cout << "YES\n";
		else cout << "NO\n";
	}
	cout << "END OF OUTPUT\n";
	
	return 0;
}
