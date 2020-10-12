/*
	우리는 입력된 값 A, B, C를 문제에서 알려준 방법을 통해 동일한 3개의 값으로 나누어야됨
	--> (A + B + C)가 3의 배수가 아니라면 애초에 불가능!
	
	(A + B + C) 가 3의 배수라면 BFS 탐색을 통해 가능한 모든 경우를 탐색해보자
	1) A, B에 대해서 조취를 취하는 경우
	min(A, B) + min(A, B) / max(A, B) - min(A, B) / C 

	2) A, C에 대해서 조취를 취하는 경우
	min(A, C) + min(A, C) / max(A, C) - min(A, C) / B

	3) B, C에 대해서 조취를 취하는 경우
	min(B, C) + min(B, C) / max(B, C) - min(B, C) / A

	이때, 우리가 (A + B + C)의 값을 알고 있다면
	가장 작은 값, 큰 값만 알면 나머지 값이 유추가 되므로
	visited[a][b] := (최소값 a, 최대값 b)인 경우가 있었는지! 로 잡으면 된다.

*/

#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int A, B, C, S;
bool visited[1001][1001]; // visited[A][B] := 가장 작은 값이 A, B인 적이 있는지
queue<pair<int, int>> q;

void step(int x, int y) {
	y -= x;
	x += x;
	int z = (S - x - y);
	// (x, y, z) 가 새로운 세트!
	int minR = min(x, min(y, z)), maxR = max(x, max(y, z));

	if (minR < 1) return;
	if (1000 < maxR) return;
	if (visited[minR][maxR]) return;

	q.push({ minR, maxR });
	visited[minR][maxR] = 1;
	
	return;
}


bool bfs(void) {
	int minR = min(min(A, B), C), maxR = max(max(A, B), C);

	q.push({ minR, maxR });
	visited[minR][maxR] = 1;

	while (!q.empty()) {
		int a = q.front().first, b = q.front().second;
		int c = (S - a - b);
		q.pop();

		if (a == b && b == c) return true;
		
		step(min(a,b), max(a,b));
		step(min(a,c), max(a,c));
		step(min(b,c), max(b,c));
	}

	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> A >> B >> C;
	S = (A + B + C);

	bool ans = true;

	if (S % 3) ans = false;
	else ans = bfs();

	cout << ans << '\n';

	return 0;
}
