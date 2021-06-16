#include<iostream>
#include<queue>
#include<map>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, L, P, M, x;
	string op;
	map<int, int> problemMap;
	priority_queue<pair<int, int>> hardProblem;
	priority_queue<pair<int, int>> easyProblem;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> P >> L;
		problemMap.insert({ P, L });
		hardProblem.push({ L, P });
		easyProblem.push({ -L, -P });
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> op;
		if (op == "recommend") {
			cin >> x;
			if (x == 1) { // 어려운문제뽑자
				while (!hardProblem.empty()) {
					int curL = hardProblem.top().first;
					int curP = hardProblem.top().second;
					if (problemMap.find(curP) != problemMap.end() &&
						problemMap.find(curP)->second == curL) {
						cout << curP << '\n';
						break;
					}
					hardProblem.pop();
				}
			}
			else if (x == -1) {
				while (!easyProblem.empty()) {
					int curL = -easyProblem.top().first;
					int curP = -easyProblem.top().second;
					if (problemMap.find(curP) != problemMap.end() &&
						problemMap.find(curP)-> second == curL) {
						cout << curP << '\n';
						break;
					}
					easyProblem.pop();
				}
			}
		}
		else if (op == "add") {
			cin >> P >> L;
			problemMap.insert({ P, L });
			hardProblem.push({ L, P });
			easyProblem.push({ -L, -P });
		}
		else if (op == "solved") {
			cin >> P;
			problemMap.erase(P);
		}
	}
}
