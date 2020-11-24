/*
	단순 구현 문제
	
	* 이동한 파이어볼과 기존의 파이어볼의 정보를 따로 저장해야되므로 2개의 map이 필요
	* 파이어볼이 같은 칸에 여러 개 존재하므로 vector로 입력을 받는다.
	* 파이어볼이 d 방향으로 s 속도만큼 이동하면 범위를 벗어날 수 있음
	--> curX + dx[d] * s , curY + dy[d] * s 를 하면 새로운 이동 좌표가 나옴.
		이때, 양수가 나오면 문제가 없으나 음수가 나오면 % N 이 원하는대로 작동하지 않기 때문에 추가 작업 필요.
	--> 적당히 큰 값인 1000 * N 을 더해줘서 양수로 돌리고 % N 을 이용해서 새로운 좌표를 바로 구할 수 있다.
*/

#include<iostream>
#include<vector>

using namespace std;

struct fireball {
	int m, s, d;
};

int N, M, K;
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
vector<fireball> map[50][50];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> K;
	for (int i = 0, r, c, m, s, d; i < M; i++) {
		cin >> r >> c >> m >> s >> d;
		r--, c--;
		map[r][c].push_back({ m, s, d });
	}
	int jump = 1000 * N;
	while (K--) {
		vector<fireball> tempMap[50][50] = {};
		// fireball 이동 후 tempMap에 저장
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < map[i][j].size(); k++) {
					int nextX = i + dx[map[i][j][k].d] * map[i][j][k].s, nextY = j + dy[map[i][j][k].d] * map[i][j][k].s;
					nextX = (nextX + jump) % N, nextY = (nextY + jump) % N;
					tempMap[nextX][nextY].push_back(map[i][j][k]);
				}
			}
		}
		// map clear
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				map[i][j].clear();
		// tempMap에 있는 파이어볼들을 합쳐서 map에 저장하자.
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if ((int)tempMap[i][j].size() >= 2) {
					fireball temp = { 0, 0, 0 };
					bool even = false, odd = false;
					for (int k = 0; k < tempMap[i][j].size(); k++) {
						temp.m += tempMap[i][j][k].m;
						temp.s += tempMap[i][j][k].s;
						if (tempMap[i][j][k].d % 2) odd = true;
						else even = true;
					}
					temp.m /= 5;
					temp.s /= (int)tempMap[i][j].size();
					if (temp.m == 0) continue; // 파이어볼이 사라짐
					if ((!even && odd) || (even && !odd)) {
						for (int dir = 0; dir < 8; dir += 2)
							map[i][j].push_back({ temp.m, temp.s, dir });
					}
					else {
						for (int dir = 1; dir < 8; dir += 2)
							map[i][j].push_back({ temp.m, temp.s, dir });
					}
				}
				else{
					map[i][j] = tempMap[i][j];
				}
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < map[i][j].size(); k++)
				ans += map[i][j][k].m;
	cout << ans << '\n';

	return 0;
}
