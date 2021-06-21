/*
  Brute Force
  
  오름차순으로 값이 입력되므로 
  앞에서부터 모든 타일마다 뒤에 타일과의 차이만큼 더 차이나는 3번 째 타일이 있는지 체크한다.
  --> 3개의 연속된 타일이 존재한다면 그 차이만큼 더 탐색을 진행한다.
  --> 3개의 연속된 타일이 존재하지않는다면 넘어간다.
  
 #주의#
  답이 int 범위를 넘어선다. --> 빠르게 캐치 못해서 틀렸습니다 2번 받음...!! 반성하자...
  입력되는 값의 범위가 1 ~ 1,000,000 이므로 tile 배열을 선언해서 다음 값이 있는지 바로 체크하면 된다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, list[3000];

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> list[i];

	bool tile[1000001] = {};
	for (int i = 0; i < N; i++)
		tile[list[i]] = true;

	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			int jump = list[j] - list[i];
			if (jump == 0) continue;
			if (!(list[i] + 2 * jump <= 1000000 && tile[list[i] + 2 * jump])) continue;
			int temp = 3 * (list[i] + jump);
			for (int k = 3; ; k++) {
        if (!(list[i] + k * jump <= 1000000 && tile[list[i] + k * jump])) break;
        temp += list[i] + k * jump;
			}
			ans = max(ans, temp);
		}
	}
	cout << ans << '\n';

	return 0;
}
