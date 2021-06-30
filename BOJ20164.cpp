/*
* 브루트포스
*/
#include<iostream>
#include<string>
#include<algorithm>
#include<queue>

using namespace std;

string intToString(int n) {
	string res = "";
	while (n) {
		res.push_back((n % 10) + '0');
		n /= 10;
	}
	reverse(res.begin(), res.end());

	return res;
}

int countOddNum(string n) {
	int res = 0;
	for (int i = 0; i < n.length(); i++)
		if ((n[i] - '0') % 2 == 1)
			res++;
	return res;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	string N;
	
	cin >> N;

	queue<pair<string, int>> q;
	q.push({ N, countOddNum(N) });
	int minAns = 99999999, maxAns = -1;

	while (!q.empty()) {
		string curS = q.front().first;
		int curOddCnt = q.front().second;
		q.pop();
		
		if (curS.length() == 1) {
			minAns = min(minAns, curOddCnt);
			maxAns = max(maxAns, curOddCnt);
		}
		else if (curS.length() == 2) {
			string nextS = intToString((curS[0] - '0') + (curS[1] - '0'));
			q.push({ nextS, curOddCnt + countOddNum(nextS) });
		}
		else if(curS.length() >= 3){
			for (int i = 1; i < curS.length() - 1; i++) {
				for (int j = i + 1; j < curS.length(); j++) {
					// curS[0 ~ (i - 1)] curS[i ~ (j - 1)] curS[j ~ ] 3등분으로 나누자
					string nextS = intToString(
						stoi(curS.substr(0, i)) + stoi(curS.substr(i, (j - i))) + stoi(curS.substr(j)));
					q.push({ nextS, curOddCnt + countOddNum(nextS) });
				}
			}
		}
	}

	cout << minAns << ' ' << maxAns << '\n';

	return 0;
}
