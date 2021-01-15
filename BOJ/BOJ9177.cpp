/*
	3중 포인터를 활용한 BFS

	입력으로 들어온 문자열 A, B, C를 가리키는 
	3개의 index 포인터로 BFS 탐색을 진행하면 된다.
	A, B index 포인터가 어디를 가르키는지 알면
	C index 포인터가 어디를 가르키는지 알 수 있으므로
	visited 배열을 A, B index를 담고있는 2차원으로 선언.

*/
#include<iostream>
#include<queue>
#include<tuple>

using namespace std;

int N;
string A, B, C;


int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int t = 1; t <= N; t++) {
		cin >> A >> B >> C;
		// 3중 포인터를 이용하자.
		queue<tuple<int, int, int>> q;
		bool visited[201][201] = {};

		q.push(make_tuple(0, 0, 0));
		visited[0][0] = true;

		bool ans = false;
		while (!q.empty()) {
			tuple<int, int, int> cur = q.front();
			q.pop();

			int i = get<0>(cur), j = get<1>(cur), k = get<2>(cur);
			if (k == C.length()) {
				ans = true;
				break;
			}

			if (i < A.length() && A[i] == C[k] && !visited[i + 1][j]) {
				q.push(make_tuple(i + 1, j, k + 1));
				visited[i + 1][j] = true;
			}
			if (j < B.length() && B[j] == C[k] && !visited[i][j + 1]) {
				q.push(make_tuple(i, j + 1, k + 1));
				visited[i][j + 1] = true;
			}
		}
		ans ? (cout << "Data set " << t << ": yes\n") :
			(cout << "Data set " << t << ": no\n");
	}
}
