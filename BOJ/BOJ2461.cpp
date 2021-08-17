/*
	투 포인터
  
  학생들을 능력 순으로 정렬 한 후 i 부터 j 범위까지 본다.
  이때, N개의 서로 다른 학급 반 학생이 모였다면 답 갱신이 가능
  --> i번 째 학생이랑 같은 반 학생이 i ~ j범위에 이미 있다면 i를 ++ 해서 범위를 좁히는게 최소값
  --> 반 별로 학생수를 count 하면서 탐색을 진행하자.
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, M;
	vector<pair<int, int>> studentAb;

	cin >> N >> M;
	for (int classN = 1; classN <= N; classN++) {
		for (int j = 0, ability; j < M; j++) {
			cin >> ability;
			studentAb.push_back({ ability , classN });
		}
	}
	
	sort(studentAb.begin(), studentAb.end());
	
	int i = 0, j = 1, classN = 0;
	int classPerStudentCnt[1001] = {};

	classN++;
	classPerStudentCnt[studentAb[i].second]++;

	int ans = 999999999;
    if(N == 1) 
        ans = 0;
    
	while (j < N * M) {
		int curClass = studentAb[j].second;

		classPerStudentCnt[curClass]++;
		if (classPerStudentCnt[curClass] == 1)
			classN++;

		while (classPerStudentCnt[studentAb[i].second] > 1) {
			classPerStudentCnt[studentAb[i].second]--;
			i++;
		}

		if (classN >= N) { // 현재 모든 반 학생이 모임
			ans = min(ans, studentAb[j].first - studentAb[i].first);
		}

		j++;
	}
	cout << ans << '\n';

	return 0;
}
