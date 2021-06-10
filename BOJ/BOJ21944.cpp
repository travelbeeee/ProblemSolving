#include<iostream>
#include<map>
#include<queue>

using namespace std;

map<int, pair<int, int>> problemMap; // {문제번호 : {난이도, 알고리즘분류}}
priority_queue<pair<int, int>> rc1_hardProblem[101]; // recommend G x = 1
priority_queue<pair<int, int>> rc1_easyProblem[101]; // recommend G x = -1
priority_queue<pair<int, pair<int, int>>> rc2_hardProblem; // recommend2 x = 1
priority_queue<pair<int, pair<int, int>>> rc2_easyProblem; // recommend2 x = -1
priority_queue<pair<int, int>> rc3_minProblem[101]; // recommend3 x = 1
priority_queue<pair<int, int>> rc3_maxProblem[101]; // recommend3 x= -1

void insertProblem(int P, int L, int G) {
	rc1_hardProblem[G].push({ L, P });
	rc1_easyProblem[G].push({ -L, -P });
	rc2_hardProblem.push({ L, {P, G} });
	rc2_easyProblem.push({ -L, { -P, -G} });
	rc3_minProblem[L].push({ -P, -G });
	rc3_maxProblem[L].push({ P, G });
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, M, P, L, G, x;
	string op;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> P >> L >> G; // 문제번호, 난이도, 알고리즘분류
		problemMap.insert({ P, {L, G} });
		insertProblem(P, L, G);
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> op;
		if (op == "add") {
			cin >> P >> L >> G;
			problemMap.insert({ P, {L, G} });
			insertProblem(P, L, G);
		}
		else if (op == "solved") {
			cin >> P;
			problemMap.erase(P);
		}
		else if (op == "recommend") {
			cin >> G >> x;
			if (x == 1) {
				while (!rc1_hardProblem[G].empty()) {
					L = rc1_hardProblem[G].top().first;
					P = rc1_hardProblem[G].top().second;
					if (problemMap.find(P) != problemMap.end()
						&& problemMap[P].first == L && problemMap[P].second == G) {
						cout << P << '\n';
						break;
					}
					rc1_hardProblem[G].pop();
				}
			}	
			else if (x == -1) {
				while (!rc1_easyProblem[G].empty()) {
					L = -rc1_easyProblem[G].top().first;
					P = -rc1_easyProblem[G].top().second;
					if (problemMap.find(P) != problemMap.end() &&
						problemMap[P].first == L && problemMap[P].second == G) {
						cout << P << '\n';
						break;
					}
					rc1_easyProblem[G].pop();
				}
			}
		}
		else if (op == "recommend2") {
			cin >> x;
			if (x == 1) {
				while (!rc2_hardProblem.empty()) {
					L = rc2_hardProblem.top().first;
					P = rc2_hardProblem.top().second.first;
					G = rc2_hardProblem.top().second.second;
					if (problemMap.find(P) != problemMap.end() &&
						problemMap[P].first == L && problemMap[P].second == G) {
						cout << P << '\n';
						break;
					}
					rc2_hardProblem.pop();
				}
			}
			else if (x == -1) {
				while (!rc2_easyProblem.empty()) {
					L = -rc2_easyProblem.top().first;
					P = -rc2_easyProblem.top().second.first;
					G = -rc2_easyProblem.top().second.second;
					if (problemMap.find(P) != problemMap.end() &&
						problemMap[P].first == L && problemMap[P].second == G) {
						cout << P << '\n';
						break;
					}
					rc2_easyProblem.pop();
				}
			}
		}
		else if (op == "recommend3") {
			cin >> x >> L;
			bool isFind = false;
			if (x == 1) {
				for (int i = L; i <= 100; i++) {
					while (!rc3_minProblem[i].empty()) {
						P = -rc3_minProblem[i].top().first;
						G = -rc3_minProblem[i].top().second;
						if (problemMap.find(P) != problemMap.end() &&
							problemMap[P].first == i && problemMap[P].second == G) {
							cout << P << '\n';
							isFind = true;
							break;
						}
						rc3_minProblem[i].pop();
					}
					if (isFind) break;
				}
			}
			else if (x == -1) {
				for (int i = L - 1; i >= 1; i--) {
					while (!rc3_maxProblem[i].empty()) {
						P = rc3_maxProblem[i].top().first;
						G = rc3_maxProblem[i].top().second;
						if (problemMap.find(P) != problemMap.end() &&
							problemMap[P].first == i && problemMap[P].second == G) {
							cout << P << '\n';
							isFind = true;
							break;
						}
						rc3_maxProblem[i].pop();
					}
					if (isFind) break;
				}
			}
			if (!isFind) cout << -1 << '\n';
		}
	}
	return 0;
}
