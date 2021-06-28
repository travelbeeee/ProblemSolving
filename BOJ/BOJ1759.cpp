/*
  백트레킹
  
  암호문은 오름차순이므로 백트레킹을 할 때, 
  현재 어디까지 alphbetList를 탐색했는지 정보를 넘겨줘서 쓸모없는 탐색을 방지한다. 
*/
#include<iostream>
#include<algorithm>

using namespace std;

int L, C;
char alp[15];
string cipher;

bool checkVowel(char c) {
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return true;
	return false;
}

void backtracking(int s, int len) {
	if (len == L) {
		int consonant = 0, vowel = 0;
		for (int i = 0; i < len; i++){
			if(checkVowel(cipher[i])) vowel++;
			else consonant++;
		}
		if(!(1 <= vowel && 2 <= consonant)) return;

		cout << cipher << '\n';
		return;
	}
	
	for (int i = s; i < C; i++) {
		cipher.push_back(alp[i]);
		backtracking(i + 1, len + 1);
		cipher.pop_back();
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> L >> C;
	for (int i = 0; i < C; i++)
		cin >> alp[i];

	sort(alp, alp + C);

	backtracking(0, 0);
	
	return 0;
}
