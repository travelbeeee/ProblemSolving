/*
	dmap[N] 
	= "12" + dmap[N - 1],
		"34" + dmap[N - 2],
		dmap[N - 2] + "34",
		"56" + dmap[N - 3],
		dmap[N - 3] + "56", ... ,
		"1" + dmap[N / 2] + "2",
		"3" + dmap[N / 3] + "4",
		"5" + dmap[N / 5] + "6" 중에 제일 작은 값이다.
*/
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

string cmp(string A, string B) {
	if (A.length() < B.length()) return A;
	else if (A.length() > B.length()) return B;

	for (int i = 0; i < A.length(); i++)
		if (A[i] < B[i]) return A;
		else if (A[i] > B[i]) return B;
	
	return A;
}

string getDmap(int n, vector<string> &dmap) {
	string minValue = "12" + dmap.at(n - 1);
	for (int j = 2; j < n; j++)
		minValue = cmp(minValue, dmap.at(j) + dmap.at(n - j));

	if (n % 2 == 0)
		minValue = cmp(minValue, ("1" + dmap.at(n / 2) + "2"));
	if (n % 3 == 0)
		minValue = cmp(minValue, ("3" + dmap.at(n / 3) + "4"));
	if (n % 5 == 0)
		minValue = cmp(minValue, ("5" + dmap.at(n / 5) + "6"));

	return minValue;
}

void printDmap(string dmap) {
	for (int i = 0; i < dmap.length(); i++){
		if (dmap[i] == '1') cout << '(';
		else if (dmap[i] == '2') cout << ')';
		else if (dmap[i] == '3') cout << '{';
		else if (dmap[i] == '4') cout << '}';
		else if (dmap[i] == '5') cout << '[';
		else if (dmap[i] == '6') cout << ']';
	}
	cout << '\n';
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	vector<string> dmap(1001);
	dmap[1] = "12";
	dmap[2] = "34";
	dmap[3] = "56";
	for (int i = 4; i <= 1000; i++) {
		dmap[i] = getDmap(i, dmap);
	}

	int T, N;
	cin >> T;
	while (T--) {
		cin >> N;
		printDmap(dmap[N]);
	}
	return 0;
}
