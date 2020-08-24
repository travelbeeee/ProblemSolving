/*
	피자의 조각이 최대 1000개이고, 피자 조각의 최대 크기도 1000이므로
	모든 연속된 피자 조각의 합을 구하는 O(N^2) 알고리즘을 사용해도 괜찮고,
	최대 피자 조각의 합 크기도 1000 * 1000 밖에 안되므로
	모든 연속된 피자 조각의 합을 다 구해서 count를 저장해놓을 수 있다.
	--> A / B 피자에서 만들 수 있는 모든 조각을 다 구해놓는다.
	--> client 가 원하는 값을 A / B 피자에서 선택해서 만드는 경우 쉽게 계산 가능.
*/

#include<iostream>

using namespace std;

int client, nA, nB;
int pizzaA[1000], pizzaB[1000]; // pizza 조각들
int sizeA[1000001] = {}, sizeB[1000001] = {}; // pizza 조각으로 만들 수 있는 크기 count
int ans = 0;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> client >> nA >> nB;
	for (int i = 0; i < nA; i++)
		cin >> pizzaA[i];
	for (int i = 0; i < nB; i++)
		cin >> pizzaB[i];

	// pizzaA, pizzaB의 조각들로 만들 수 있는 모든 크기를 다 구하자.
	// --> 먼저 크기 0은 아무것도 안 선택하면 되므로 1로 셋팅!
	// --> 모든 조각을 다 선택한 경우만 따로 먼저 셋팅해준다.
	sizeA[0] = 1, sizeB[0] = 1; 
	int sum = 0;
	for (int i = 0; i < nA; i++)
		sum += pizzaA[i];
	sizeA[sum]++;
	sum = 0;
	for (int i = 0; i < nB; i++)
		sum += pizzaB[i];
	sizeB[sum]++;
	// i번 째 조각에서 시작해서 모든 조각을 선택하기 전까지 연속 합들을 다 count 해준다.
	for (int i = 0; i < nA; i++) {
		int sum = 0;
		for (int j = 0; j < nA - 1; j++) {
			sum += pizzaA[(i + j) % nA];
			sizeA[sum]++;
		}
	}
	for (int i = 0; i < nB; i++) {
		int sum = 0;
		for (int j = 0; j < nB - 1; j++) {
			sum += pizzaB[(i + j) % nB];
			sizeB[sum]++;
		}
	}
	// client 가 원하는 조각을 몇 개 만들 수 있는지 count 해준다.
	for (int i = 0; i <= client; i++)
		ans += (sizeA[i] * sizeB[client - i]);

	cout << ans << '\n';
}