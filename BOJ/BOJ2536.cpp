/*
  BFS
   
  1) 시작 위치에서 탈 수 있는 모든 버스를 타면서 BFS 탐색 시작!
  2) 현재 버스에서 다른 버스로 환승이 가능하고, 
  전에 방문한 적이 없거나 전보다 더 작은 환승값으로 방문 가능하면 방문!
*/
#include<iostream>
#include<queue>

using namespace std;

struct bus{
	int x1, y1, x2, y2;
};
const int INF = 9999;
int m, n, k, sX, sY, dX, dY;
int ans;
int visited[5001];
bus busList[5001];
bool finished[5001];

/*
  busA 번 버스랑 busB번 버스랑 환승할 수 있는지!
*/
bool canTranfer(int busA, int busB) {
	if (busList[busA].y1 == busList[busA].y2 &&
		busList[busB].y1 == busList[busB].y2 && busList[busA].y1 == busList[busB].y1) { // 둘다 가로
		if ((busList[busA].x1 <= busList[busB].x1 && busList[busB].x1 <= busList[busA].x2)
			|| (busList[busA].x1 <= busList[busB].x2 && busList[busB].x2 <= busList[busA].x2))
			return true;
	}
	else if (busList[busA].x1 == busList[busA].x2 &&
		busList[busB].x1 == busList[busB].x2 && busList[busA].x1 == busList[busB].x1) { // 둘다 세로
		if ((busList[busA].y1 <= busList[busB].y1 && busList[busB].y1 <= busList[busA].y2)
			|| (busList[busA].y1 <= busList[busB].y2 && busList[busB].y2 <= busList[busA].y2))
			return true;
	}

	else { // 하나는 가로 하나는 세로! 가로를 busA로 셋팅하자
		if (busList[busA].x1 == busList[busA].x2) {
			int temp = busA;
			busA = busB;
			busB = temp;
		}
		if (busList[busA].x1 <= busList[busB].x1 && busList[busB].x1 <= busList[busA].x2 &&
			busList[busB].y1 <= busList[busA].y1 && busList[busA].y1 <= busList[busB].y2)
			return true;
	}
	return false;
}

// bus번 버스를 타고 (x,y) 지점에 갈 수 있는지
bool canArrive(int bus, int x, int y) {
	if (busList[bus].x1 == busList[bus].x2)
		if (busList[bus].x1 == x && busList[bus].y1 <= y && y <= busList[bus].y2) return true;
	if (busList[bus].y1 == busList[bus].y2)
		if (busList[bus].y1 == y && busList[bus].x1 <= x && x <= busList[bus].x2) return true;
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> m >> n >> k;
	for (int i = 1, b, x1, y1, x2, y2; i <= k; i++) {
		cin >> b >> x1 >> y1 >> x2 >> y2;
		if (x1 == x2) busList[b] = { x1, min(y1,y2), x2, max(y1,y2) };
		else if (y1 == y2) busList[b] = { min(x1, x2), y1, max(x1, x2), y2 };
		visited[i] = INF;
	}
	cin >> sX >> sY >> dX >> dY;

	// (dx, dy)에 도착할 수 있는 버스를 다 탐색하자!
	for (int i = 1; i <= k; i++) {
		if (canArrive(i, dX, dY)) {
			finished[i] = true;
		}
	}

	ans = INF;
	queue<pair<int, int>> q; // { busNum, Length }
	// (sX,sY)에서 탈 수 있는 모든 버스를 타보자!
	for (int i = 1; i <= k; i++) {
		if (canArrive(i, sX, sY)) {
			q.push({ i, 1 });
			visited[i] = 1;
		}
	}
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		if (finished[cur.first]) {
			ans = min(ans, cur.second);
			continue;
		}
		
		for (int i = 1; i <= k; i++) {
			// cur.first bus랑 i번 버스랑 갈아탈수있는걸찾자!
			if (cur.first == i) continue;
			if (canTranfer(cur.first, i) && cur.second + 1 < visited[i]) {
				visited[i] = cur.second + 1;
				q.push({ i, cur.second + 1 });
			}
		}
	}
	cout << ans << '\n';

	return 0;
}
