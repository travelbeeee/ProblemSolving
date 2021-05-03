/*
  단순 
*/
#include<iostream>
#include<vector>

using namespace std;

int N, M, A[50][50];
vector<int> cloudX, cloudY;
bool increasedBasket[50][50];
bool existedCloud[50][50];

const int dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 }, dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

void printMap(void) {
	cout << "맵출력!\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << A[i][j] << ' ';
		}
		cout << '\n';
	}
}

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < N);
}

void setInitCloud(void) {
	cloudX.push_back(N - 1);
	cloudX.push_back(N - 1);
	cloudX.push_back(N - 2);
	cloudX.push_back(N - 2);
	cloudY.push_back(0);
	cloudY.push_back(1);
	cloudY.push_back(0);
	cloudY.push_back(1);
}

void moveAllCloud(int dir, int len) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			increasedBasket[i][j] = existedCloud[i][j] = false;

	int c = cloudX.size();
	len = len % N;
	for (int i = 0; i < c; i++) {
		cloudX[i] += dx[dir] * len, cloudY[i] += dy[dir] * len;
		cloudX[i] = (cloudX[i] + N) % N;
		cloudY[i] = (cloudY[i] + N) % N;
		existedCloud[cloudX[i]][cloudY[i]] = true;
		increasedBasket[cloudX[i]][cloudY[i]] = true;
		A[cloudX[i]][cloudY[i]]++;
	}
	cloudX.clear(), cloudY.clear();
}

void waterCopy(void) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!increasedBasket[i][j]) continue;
			int cnt = 0;
			for (int k = 1; k < 9; k += 2) {
				int nextX = i + dx[k], nextY = j + dy[k];
				if (!isInside(nextX, nextY)) continue;
				if (A[nextX][nextY] > 0) cnt++;
			}
			A[i][j] += cnt;
		}
	}
}

void makeCloud(void) {
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if (A[i][j] >= 2 && !existedCloud[i][j]) {
				A[i][j] -= 2;
				cloudX.push_back(i), cloudY.push_back(j);
			}
}

int sumWater(void) {
	int res = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			res += A[i][j];
	return res;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> A[i][j];

	setInitCloud();

	for (int i = 0, d, s; i < M; i++) {
		cin >> d >> s;

		moveAllCloud(d - 1, s);

		waterCopy();

		makeCloud();
	}

	cout << sumWater() << '\n';

	return 0;
}
