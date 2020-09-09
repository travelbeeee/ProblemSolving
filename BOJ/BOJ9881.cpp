/*
  가장 낮은 언덕과 가장 큰 언덕의 높이 차이가 17 이내라면 세금 면제
  --> 낮은 언덕을 쌓고, 큰 언덕은 깎아서 높이 차이가 17 이내로 만들어야된다.
  --> 언덕을 k 만큼 쌓거나 깎는데 k * k 만큼의 cost 발생
  
  언덕의 높이 범위가 0 ~ 100 으로 굉장히 작다
  --> 0 ~ 17 / 1 ~ 18 / ... / 83 ~ 100 으로 17 차이를 가지는 모든 범위를 만들어서 언덕을 바꿔본다.
*/
#include<iostream>
#include<algorithm>
using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, hills[1000];

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> hills[i];

	int ans = 99999999;
	for (int i = 0; i <= 100 - 17; i++) {
		// i ~ i + 17 까지가 우리가 잡은 범위!
		int tempAns = 0;
		for (int j = 0; j < N; j++) {
			if (hills[j] < i) tempAns += (i - hills[j]) * (i - hills[j]);
			if (hills[j] > i + 17) tempAns += (hills[j] - i - 17) * (hills[j] - i - 17);
		}
		ans = min(ans, tempAns);
	}
	cout << ans << '\n';
}
