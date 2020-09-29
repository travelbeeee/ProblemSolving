/*
	sumA[i] := (a[0] ~ a[i]) 까지의 합
	sumB[i] := (b[0] ~ b[i]) 까지의 합
	
	--> sumA, sumB를 이용해 a, b 집합의 모든 부분합을 O(N^2) 으로 구할 수 있다.
	--> 모든 부분합 subA, subB 에서 합쳐서 T가 나오는 모든 쌍을 구하면 된다.
	--> 시간 복잡도 때문에 binary_Search 이용!
	--> binary_Search를 이용하기 위해 subB를 미리 전처리해주자!
	--> countedSubB 는 { subB의 값, 그 값이 몇 개 있는지 } 를 저장해주면 된다.
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T, n, m;
	int a[1000], b[1000];
	int sumA[1000], sumB[1000];

	cin >> T >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	cin >> m;
	for (int i = 0; i < m; i++) cin >> b[i];

	sumA[0] = a[0], sumB[0] = b[0];
	for (int i = 1; i < n; i++)
		sumA[i] = a[i] + sumA[i - 1];
	for (int i = 1; i < m; i++)
		sumB[i] = b[i] + sumB[i - 1];

	vector<int> subA, subB;
	for (int i = 0; i < n; i++){
		subA.push_back(sumA[i]);
		for (int j = i + 1; j < n; j++)
			subA.push_back(sumA[j] - sumA[i]);
	}
	for (int i = 0; i < m; i++){
		subB.push_back(sumB[i]);
		for (int j = i + 1; j < m; j++)
			subB.push_back(sumB[j] - sumB[i]);
	}

	long long ans = 0;
	sort(subB.begin(), subB.end());
	vector<pair<int, int>> countedSubB;
	int i = 0;
	while (i < subB.size()) {
		int cnt = 0, j = i;
		while (j < subB.size() && subB[i] == subB[j]) {
			j++, cnt++;
		}
		countedSubB.push_back({ subB[i], cnt });
		i = j;
	}

	for (int i = 0; i < subA.size(); i++) {
		int l = 0, r = (int)countedSubB.size() - 1;
		while (l <= r) {
			int m = (l + r) / 2;
			if (subA[i] + countedSubB[m].first == T) {
				ans += countedSubB[m].second;
				break;
			}
			else if (subA[i] + countedSubB[m].first < T)
				l = m + 1;
			else
				r = m - 1;
		}
	}
	cout << ans << '\n';

	return 0;
}
