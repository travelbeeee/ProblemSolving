/*
	자료구조 Map, PriorityQueue를 이용해서 시뮬레이션을 해결한다

	computerUsage[i] := i번 컴퓨터 사용 횟수
	
	map<int, int> usingComputer = { 사용자id, 사용중인컴퓨터id }
	--> 사용자가 다 이용하고 Out하는 경우에는 emptyComputer 목록에 컴퓨터id를 넣어준다

	priority_queue<int> emptyComputer = { -빈컴퓨터id }
	--> 현재 비어있는 컴퓨터 중 가장 번호가 작은 컴퓨터를 알려준다

	기본적으로 emptyComputer가 없으면 Computer를 불가피하게 추가해야되는 경우이다.
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, P, Q;
	vector<pair<int, pair<bool, int>>> people;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> P >> Q;
		people.push_back({ P, {true, i} });
		people.push_back({ Q, {false, i} });
	}

	sort(people.begin(), people.end());

	int computerId = 1;
	int computerUsage[100001] = {};
	priority_queue<int> emptyComputer;
	map<int, int> usingComputer;

	for (int i = 0; i < people.size(); i++) {
		if (people[i].second.first == true) { // 들어오는사람
			if (emptyComputer.empty()) {
				computerUsage[computerId]++;
				usingComputer.insert({ people[i].second.second, computerId, });
				computerId++;
			}
			else {
				int emptyComputerId = -emptyComputer.top();
				emptyComputer.pop();
				computerUsage[emptyComputerId]++;
				usingComputer.insert({ people[i].second.second, emptyComputerId, });
			}
		}
		else { // 나가는사람
			int usingComputerId = usingComputer[people[i].second.second];
			emptyComputer.push(-usingComputerId);
		}
	}
	cout << computerId - 1<< '\n';
	for (int i = 1; i < computerId; i++)
		cout << computerUsage[i] << ' ';
	return 0;
}
