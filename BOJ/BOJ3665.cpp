/*
	Cycle찾기 위상정렬

	실제로는 위상정렬보다는 Cycle을 찾는게 더 핵심인 문제인 것 같다.

	1) 작년 순위를 입력받으면 그에 해당하는 2차원 배열을 만든다.
	map[i][j] := (i --> j)로 간선이 존재한다는 뜻이고 i가 j 보다 높은 등수라는 뜻
	* 그 뒤의 m개의 입력 때문에 2차원 배열로 입력을 받는다.

	2) 편의를 위해 입력받은 그래프를 2차원 배열에서 vector 로 바꿔서 표현해준다.

	3) Cycle이 나온다면 순위를 정할 수 없는 경우 "IMPOSSIBLE" 이다.
	* 확실한 순위를 찾을 수 없는 경우는 없다. 왜냐하면 작년 순위가 들어오고 그 순위를 변동한 것이므로 불가능하거나 가능하다.

	4) Cycle이 없다면 위상정렬로 차례대로 순회하며 출력해주면 된다.
*/
#include<iostream>
#include<queue>

using namespace std;

int T, n, m, a, b;
int ranking[500];
vector<int> graph[500];
bool map[500][500]; // map[i][j] := i --> j 로 간선
bool visited[500];

void init(void) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			map[i][j] = false;

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			map[ranking[i]][ranking[j]] = true;
	
	for (int i = 0; i < n; i++) graph[i].clear();
}

void setGraph(void) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (map[i][j]) graph[i].push_back(j);
}

bool findCycle(int start, int cur) {
	if (visited[cur]) {
		if (start == cur) return true;
		return false;
	}

	visited[cur] = true;

	for (int there : graph[cur])
		if (findCycle(start, there)) return true;
	return false;
}

bool checkImpossible(void) {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++) 
			visited[j] = false;
		if (findCycle(i, i)) {
			return true;
		}
	}
	return false;
}

void topologicalSort(void) {
	int preOrder[500] = {};
	for (int i = 0; i < n; i++)
		for (int there : graph[i])
			preOrder[there]++;


	queue<int> q;
	for (int i = 0; i < n; i++)
		if (!preOrder[i]) q.push(i);

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		cout << cur + 1 << ' ';
		for (int there : graph[cur]) {
			preOrder[there]--;
			if (!preOrder[there]) q.push(there);
		}
	}
	cout << '\n';
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> ranking[i];
			ranking[i]--;
		}

		init();
		
		cin >> m;
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			a--, b--;
			if (map[a][b]) {
				map[a][b] = false;
				map[b][a] = true;
			}
			else {
				map[b][a] = false;
				map[a][b] = true;
			}
		}

		setGraph();

		if (checkImpossible()) {
			cout << "IMPOSSIBLE\n";
			continue;
		}
		topologicalSort();
	}
	return 0;
}
