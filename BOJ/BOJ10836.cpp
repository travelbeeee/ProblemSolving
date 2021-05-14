/*
  구현
  
  무작정 구현하면 O(N * M * M) 으로 시간초과가 발생한다
  --> 문제에서 나온 힌트를 이용
  --> 애벌레 크기는 항상 왼쪽 위, 왼쪽, 위 중에 가장 큰 값으로 바뀐다
  --> 입력으로 주어지는 가장 왼쪽 열, 위 행만 N번 입력받아서 값을 증가시키고,
    나머지 애벌레들은 N일이 지난 후에 한 번에 증가시키자.
*/
#include<iostream>
#include<algorithm>

using namespace std;

int N, M;
int map[700][700];

void printMap() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << ' ';
		}
		cout << '\n';
	}
}

void setMap() {
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			map[i][j] = 1;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> M >> N;

	// Map 셋팅
	setMap();

	// N일동안 애벌레 변화 --> 맨 왼쪽열 위행
	int zero, one, two;
	for (int i = 0; i < N; i++) {
		cin >> zero >> one >> two;
		// 맨왼쪽열 아래부터 위로
		for (int i = M - 1; i >= 0; i--) {
			if (zero) {
				map[i][0] += 0;
				zero--;
			}
			else if (one) {
				map[i][0] += 1;
				one--;
			}
			else if (two) {
				map[i][0] += 2;
				two--;
			}
		}
		// 맨위행 왼쪽부터 오른쪽으로
		for (int j = 1; j < M; j++) {
			if (zero) {
				map[0][j] += 0;
				zero--;
			}
			else if (one) {
				map[0][j] += 1;
				one--;
			}
			else if (two) {
				map[0][j] += 2;
				two--;
			}
		}
	}
  // 나머지 애벌레 
	for (int i = 1; i < M; i++)
		for (int j = 1; j < M; j++) 
			map[i][j] =  max(map[i - 1][j], max(map[i - 1][j - 1], map[i][j - 1]));
  
	// 답출력
	printMap();
}
