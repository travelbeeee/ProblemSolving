/*
*	처음에 완전 브루트포스하게 접근했으나 시간초과 발생...!
	
	입력되는 문자열마다 문자열 길이만큼 모든 지점을 탐색해서 count
	--> K번 N * M 크기의 모든 지점에서 8방향으로 len(K)만큼 탐색하므로
	--> O( K * N * M * 8^(len(K)) )
	--> 시간초과 발생!

	반복되는 경우의 수를 줄여주자!

	N * M 크기에서 8방향으로 5길이만큼 미리 다 탐색해서
	Map에 해당 문자열이 몇 번 등장했는지 저장해두자.
	--> O( N * M * 8^5 ) 
	--> 그리고 입력되는 문자열이 몇 개 나왔는지 count해주자.
*/
#include<iostream>
#include<queue>
#include<map>

using namespace std;

const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

int N, M, K;
char tile[10][11];
map<string, int> godStrMap;
string str;

// (x, y) 에서 맘대로 최대 5번 이동해서 만들 수 있는 모든 문자열을 만들어 Map에 쌓자.
void BFS(int x, int y) {
	queue<pair<pair<int, int>, string>> q;
	string cur = "";

	cur.push_back(tile[x][y]);
	q.push({ {x, y}, cur });
	if (godStrMap.find(cur) == godStrMap.end()) godStrMap.insert({ cur, 1 });
	else godStrMap[cur]++;

	for (int l = 1; l < 5; l++) {
		int size = q.size();
		for (int s = 0; s < size; s++) {
			pair<int, int> curP = q.front().first;
			string curS = q.front().second;
			q.pop();

			for (int d = 0; d < 8; d++) {
				int nextX = curP.first + dx[d];
				int nextY = curP.second + dy[d];
				if (nextX == -1) nextX = N - 1;
				else if (nextX == N) nextX = 0;
				if (nextY == -1) nextY = M - 1;
				else if (nextY == M) nextY = 0;
        
				string nextS = curS;
				nextS.push_back(tile[nextX][nextY]);
				q.push({ {nextX, nextY}, nextS });

				if (godStrMap.find(nextS) == godStrMap.end()) godStrMap.insert({ nextS, 1 });
				else godStrMap[nextS]++;
			}
		}
	}
}

void makePermutationOfStr() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			BFS(i, j);
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> tile[i][j];

	makePermutationOfStr();

	for (int i = 0; i < K; i++) {
		cin >> str;
		if (godStrMap.find(str) == godStrMap.end()) cout << 0 << '\n';
		else cout << godStrMap[str] << '\n';
	}

	return 0;
}
