/*
	BinarySearch

	목표 길이 X(cm) 와 레고길이 L1, L2, ... 이 있다고 하자
	
	우리는 레고 하나하나 짝을 찾아볼 것이다.
	n이 10^6 이므로 O(nlogn) 으로 문제를 해결해야한다.
	--> 짝을 찾는 과정을 sorting + binarySearch 로 해결해야한다.
	--> sorting 후 맨 앞 레고부터 그 뒤 레고들 중에 짝이 있는지 찾아보자.
	--> 짝이 있따면, L1 - L2가 가장 큰 짝이 된다. ( sorting 했으므로 )
	
	##주의할점##
	while(cin.eof()) 로 입력을 받으면 안된다!
	while(cin >> x)로 해야된다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

const long long changer = 10000000;

int n;
long long x, list[1000000];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	while (cin >> x) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> list[i];
		
		x *= changer;
		sort(list, list + n);

		int ind = 0;
		bool ans = false;
		while (ind < n) { // list[ind] 와 짝이되는 레고를 찾자! (ind + 1 ~ n - 1) 범위에서
			int left = ind + 1, right = n - 1;
			while (left <= right) {
				int mid = (left + right) / 2;
				if (list[ind] + list[mid] == x) { // 짝을 찾으면 얘가 원하는 답이 된다.
					cout << "yes " << list[ind] << ' ' << list[mid] << '\n';
					ind = n, ans = true;
					break;
				}
				else if (list[ind] + list[mid] < x) {
					left = mid + 1;
				}
				else {
					right = mid - 1;
				}
			}
			ind++;
		}
		if (!ans) cout << "danger\n";
	}
}
