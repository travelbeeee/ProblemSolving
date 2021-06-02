/*
  구현
  완전 브루트포스하게 N일 동안 M * M 칸들을 순회하며 진화시켜주면
  O(N * M * M) 으로 무조건 시간초과가 발생한다!
  
  1) 맨왼쪽열, 맨위쪽행을 제외하고 나머지들은 N일이 모두 지나고 나서 한 번에 진화를 시켜줘도 괜찮다!
  어차피 맨 왼쪽열, 맨 위쪽행을 제외하고 나머지 칸들은 
  맨 왼쪽열, 맨 위쪽행이 N일 동안 얼마나 진화했는지에 따라 최종 진화 정도가 달라진다.
  --> O(N * (2 * M - 1)) 로 복잡도를 줄이자!
  
  이렇게 해도 시간초과가 발생한다.
  --> 맨 왼쪽열, 맨 위쪽 행 중에서 zero 값은 진화가 없다
  --> one, two 값만 진화를 신경써서 복잡도를 조금이라도 더 줄여주자...!!
  --> 빅오표기법으로서는 차이가 없지만 (2 * M - 1) 칸을 순회하는  그래도 3분의 2로 복잡도를 줄일 수 있다.
  --> O(N * (2 * M - 1))
*/
#include<iostream>

using namespace std;

int M, N, map[700][700] = {}, sideGrowth[1400 - 1] = {};
int zero, one, two;

void set(){
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			map[i][j] = 1;
}

void pritnMap() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++)
			cout << map[i][j] << ' ';
		cout << '\n';
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> M >> N;

	set();

	for (int i = 0; i < N; i++) {
		cin >> zero >> one >> two;
		for (int j = zero; j < 2 * M - 1; j++) {
			if (one) {
				sideGrowth[j] += 1;
				one--;
			}
			else if (two) {
				sideGrowth[j] += 2;
				two--;
			}
		}
	}

	for (int i = M - 1; i >= 0; i--)
		map[i][0] += sideGrowth[(M - 1) - i];
	for (int j = 1; j < M; j++)
		map[0][j] += sideGrowth[(M - 1) + j];

	for (int i = 1; i < M; i++)
		for(int j = 1; j < M; j++)
			map[i][j] = max(map[i - 1][j - 1], max(map[i - 1][j], map[i][j - 1]));
	
	pritnMap();

	return 0;
}
