/*
	정렬

	크기를 기준으로 정렬을 하고 아래의 배열을 이용하면 답을 구할 수 있다.
	
	* cSum[i] := i색깔을 가진 공들의 크기의 합.

	--> 정렬 후 배열을 순회하며 순회한 모든 공 크기의 합 sum과 cSum 을 갱신해나간다.
	그러면 어떤 플레이어(j) 의 답 ans[j] = sum - cSum[j플레이어의 공색깔] 이 된다.
	하지만, 같은 크기의 공들이 연속으로 나타나는 경우는 sum, cSum 을 갱신해나가면
	답이 달라지게 된다.

	ex)
	5
	1 5
	2 7
	3 7
	4 7
	1 7

	따라서, 투포인터를 이용해 i 를 순회하며 
	i 보다 공의 크기가 작은 바로 옆 지점을 가르키는 j 를 같이 이용해야한다.

*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, ans[200001];
int cSum[200001];

vector<pair<int, pair<int, int>>> ballList;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0, a, b; i < N; i++) {
		cin >> a >> b;
		ballList.push_back({ b, {a, i + 1} });
	}

	sort(ballList.begin(), ballList.end());

	
	int j = 0, sum = 0;
	for (int i = 1; i < N; i++) {
		int s = ballList[i].first;
		int c = ballList[i].second.first;
		int idx = ballList[i].second.second;
		while (j < i && ballList[j].first < ballList[i].first) {
			sum += ballList[j].first;
			cSum[ballList[j].second.first] += ballList[j].first;
			j++;
		}
		ans[idx] = sum - cSum[c];
	}

	for (int i = 1; i <= N; i++)
		cout << ans[i] << '\n';

	return 0;
}
