/*
  1) S에 있는 알파벳 중에 T에 없는 알파벳이 없으면 만들 수 없음 --> "-1"
  2) T에 있는 알파벳 중에 S에 있는 알파벳만 뽑아서 compT 를 만들자 
  
  [ 시간초과 (76점) 구현 ]
  3) S 를 맨 앞에서부터 순회하며 S의 해당 문자 (S[sInd]) 를 찾을 때 까지 T를 계속 순회하며 T를 한 바퀴 순회하면 N을 count 해준다
  --> O(|S| * |T|) 로 시간초과 발생!
  
  3') T를 어디까지 탐색했는지 tInd에 따라 어떤 알파벳을 찾으려면 어디로 이동해야되는지 저장하고 있는 int 배열을 선언하자.
  --> |T| 는 최대 100,000 이고 알파벳은 26가지이므로 메모리 문제 OK!
  --> 그러면 S[sInd] 에 해당하는 글자를 현재 tInd 에서 어디로 이동하면 한 번에 찾을 수 있을지 캐치 가능!
  --> O(|S|) 로 찾는 과정을 복잡도를 줄일 수 있다. ( 그 대신 4 * 100,000 * 26 의 추가 공간복잡도와 100,000 * 26 의 테이블을 채우는 시간 복잡도는 추가 ) 
*/
#include<iostream>

using namespace std;

string S, T;
string compT = ""; // 필요한 부분만 압축시킨 T
bool alpS[26] = {};
bool alpT[26] = {};
// checkAlp[i]['Alphabet'] := 문자열 T의 i번 째 index부터 'Alphabet'이 뒤에 등장하
int checkAlp[100001][26] = {};

bool checkCanMakeS() {
	for (int i = 0; i < S.length(); i++)
		alpS[S[i] - 'a'] = true;
	for (int i = 0; i < T.length(); i++)
		alpT[T[i] - 'a'] = true;

	for (int i = 0; i < 26; i++)
		if (alpS[i] && !alpT[i])
			return false;
	return true;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> S >> T;

	if (!checkCanMakeS()) { // T를 아무리 반복해도 S의 줄임말이 되지 못하는 경우.
		cout << -1 << '\n';
		return 0;
	}

	for (int i = 0; i < T.length(); i++)
		if (alpS[T[i] - 'a']) compT.push_back(T[i]);

	const int M = compT.length();
	for (int j = 0; j < 26; j++)
		checkAlp[M][j] = M; // 찾을 수 없어서 한바퀴 도는 경우!

	for (int i = compT.length() - 1; i >= 0; i--) {
		for (int j = 0; j < 26; j++)
			checkAlp[i][j] = checkAlp[i + 1][j];
		checkAlp[i][compT[i] - 'a'] = i;
	}

	int N = 1, indS = 0, indT = 0;
	while (indS < S.length()) {
		indT = checkAlp[indT][S[indS] - 'a'];
		if (indT < M && S[indS] == compT[indT]) { 
			indS++, indT++;
		}
		else if (indT == M) { // 못 찾아서 다시 T를 한 바퀴 돌고 앞으로 온 경우
			indT = 0;
			N++;
		}
	}

	cout << N << '\n';

	return 0;
}
