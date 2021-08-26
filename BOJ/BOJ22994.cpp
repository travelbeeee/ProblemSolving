#include<iostream>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int n, m;
	string pic[1000];

	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> pic[i];

	int rowsMinRepeatCnt = 1000;
	int colsMinRepeatCnt = 1000;
	for (int i = 0; i < n; i++) {
		int colMinRepeatCnt = 1000, j = 0;
		while (j < m) {
			int cnt = 1;
			while (j + 1 < m && pic[i][j] == pic[i][j + 1]) {
				cnt++;
				j++;
			}
			colMinRepeatCnt = min(colMinRepeatCnt, cnt);
			j++;
		}
		colsMinRepeatCnt = min(colsMinRepeatCnt, colMinRepeatCnt);
	}
	for (int j = 0; j < m; j++) {
		int rowMinRepeatCnt = 1000, i = 0;
		while (i < n) {
			int cnt = 1;
			while (i + 1 < n && pic[i][j] == pic[i + 1][j]) {
				cnt++;
				i++;
			}
			rowMinRepeatCnt = min(rowMinRepeatCnt, cnt);
			i++;
		}
		rowsMinRepeatCnt = min(rowsMinRepeatCnt, rowMinRepeatCnt);
	}

	cout << (n / rowsMinRepeatCnt) << ' ' << (m / colsMinRepeatCnt) << '\n';
	for (int i = 0; i < n; i += rowsMinRepeatCnt) {
		for (int j = 0; j < m; j += colsMinRepeatCnt) {
			cout << pic[i][j];
		}
		cout << '\n';
	}
	return 0;
}
