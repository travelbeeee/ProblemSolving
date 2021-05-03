/*
  구현
  
  1) 얼음 파편을 던져서 구슬을 제거한다
  2) 빈 칸이 생겼기 때문에 Map을 이동해준다.
  3) 폭발을 일으킨다.
    3-1) 연속된 구슬이 4개 이상인 구슬을 지운다.
    3-2) 빈 칸이 생겼기 때문에 Map을 이동해준다.
    3-3) 더 이상 지울 구슬이 없을 때까지 반복한다.
  4) Map을 변형시켜준다.  
  
  - setPosition 함수
  우리는 2차원 배열로 N x N 격자를 표현해야된다.
  하지만, 1번칸부터 (N * N - 1)칸 까지는 상어부터 시작해서 미로를 탈출하듯이 움직여야된다.
  --> 1 ~ (N * N - 1)칸의 좌표를 미리 다 저장해두자!
  
  - getGroupSize 함수
  블리자드를 구현하기 위해서는 현재 i번 째 칸부터 연속으로 같은 구슬인 칸을 count 하는 일이 많다
  --> 따로 getGroupSize 함수로 빼서 사용
  
  - moveMap 함수
  빈 칸이 있으면 땡겨오는 함수다.
  getGroupSize 함수를 이용해서 연속된 빈 칸을 한 번에 땡겨온다
  
  - throwIce 함수
  dir 방향으로 s칸만큼 격자의 구슬을 다 지워버린다.
  
  - explosion 함수
  폭발이 더이상 없을때까지 getGroupSize 함수를 이용해서 4개 이상이 연속된 구슬을 다 지워버린다.
  
  - changeMap 함수
  getGroupSize 함수와 투 포인터를 이용해서 1번 칸부터 (N * N - 1)칸 까지 순회하며 새롭게 Map에 할당할 값들을 만든다.
  순회가 끝나거나 Map에 새롭게 할당할 값들이 1 ~ (N * N - 1) 까지 다 부여되면 끝낸다.
  
*/
#include<iostream>
#include<vector>

using namespace std;
 
int N, M, d, s, ans = 0;
int map[49][49];
vector<pair<int, int>> position;

void printMap(void) {
	cout << "맵출력\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << map[i][j] << ' ';
		cout << '\n';
	}
}

void setPosition(void) { // Map을 순회하며 1번칸부터 (N^2 - 1)칸까지 좌표를 따놓자.
	position.push_back({ -1, -1 }); // position[0] 쓰레기값

	int x = (N - 1) / 2, y = (N - 1) / 2;
	int len = 1, cnt = 0, dir = 0;
	int dx[4] = { 0, 1, 0, -1 }, dy[4] = { -1, 0, 1, 0 };
	while (1) {
		// len 크기만큼 현재 dir방향으로 이동하며 쌓아주기
		for (int l = 0; l < len; l++) {
			x += dx[dir], y += dy[dir];
			position.push_back({ x, y });
			if (x == 0 && y == 0) return;
		}
		dir = (dir + 1) % 4;
		cnt++;
		if (cnt == 2) {
			len++;
			cnt = 0;
		}
	}
}

int getGroupSize(int ind) {
	int tempInd = ind;
	while (tempInd < N * N && map[position[ind].first][position[ind].second] == map[position[tempInd].first][position[tempInd].second]) {
		tempInd++;
	}
	return tempInd - ind;
}

void moveMap(void) { // 1번 칸부터 (N * N - 1)칸까지 순회하며 빈 칸이 있으면 땡겨온다.
	int ind = 1;
	while (ind < N * N) {
		if (map[position[ind].first][position[ind].second] == 0) {
			int cnt = getGroupSize(ind); // cnt 만큼 같은 값!
			for (int j = ind; j + cnt < N * N; j++){
				map[position[j].first][position[j].second] = map[position[j + cnt].first][position[j + cnt].second];
				map[position[j + cnt].first][position[j + cnt].second] = 0;
			}
			ind += cnt;
		}
		else ind++;
	}
}

void throwIce(int dir, int len) {
	int sX = (N - 1) / 2, sY = (N - 1) / 2;
	int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };
	for (int i = 0; i < len; i++) {
		sX += dx[dir], sY += dy[dir];
		map[sX][sY] = 0;
	}
}

void explosion(void) {
	while (1) {
		bool explosition = false;

		int ind = 1;
		while (ind < N * N) {
			int cnt = getGroupSize(ind);
			if (cnt >= 4 && map[position[ind].first][position[ind].second] > 0) { // 폭발!!
				ans += cnt * map[position[ind].first][position[ind].second];
				for (int i = 0; i < cnt; i++) {
					map[position[ind + i].first][position[ind + i].second] = 0;
				}
				explosition = true;
			}
			ind += cnt;
		}

		moveMap();

		if (!explosition) return;
	}

}

void changeMap(void) {
	vector<int> newMap(N * N, 0);
	int ind = 1, newMapInd = 1;
	while (ind < N * N && newMapInd < N * N) {
		if (map[position[ind].first][position[ind].second] == 0) break;
		int groupSize = getGroupSize(ind);
		newMap[newMapInd++] = groupSize;
		newMap[newMapInd++] = map[position[ind].first][position[ind].second];
		ind += groupSize;
	}
	for (int i = 1; i < N * N; i++)
		map[position[i].first][position[i].second] = newMap[i];
	return;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	setPosition();

	int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };
	for (int i = 0; i < M; i++) {
		cin >> d >> s;

		throwIce(d - 1, s);

		moveMap();

		explosion();

		changeMap();

	}

	cout << ans << '\n';

	return 0;
}
