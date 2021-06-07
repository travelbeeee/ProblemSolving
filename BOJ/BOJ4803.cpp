/*
  Union-Find
  
  유니온-파인드를 이용해서 연결된 노드끼리 같은 집합으로 묶는다.
  이때, 이미 같은 집합에 있는 노드끼리 또 추가로 연결되는 상황이 생기면 Cycle이 생긴 상황이다
  --> Tree 가 아니다.
  
*/
#include<iostream>

using namespace std;

int N, M;
int p[501] = {};
bool checkCycle[501] = {};
bool visited[501] = {};

void set(int N) {
	for (int i = 1; i <= N; i++)
		p[i] = -1, checkCycle[i] = visited[i] = false;
}

int find(int cur) {
	if (p[cur] < 0) return cur;
	return p[cur] = find(p[cur]);
}

void merge(int a, int b) {
	int pA = find(a), pB = find(b);
	if (pA == pB) return;

	if (p[pA] < p[pB]) {
		p[pA] += p[pB];
		p[pB] = pA;
	}
	else {
		p[pB] += p[pA];
		p[pA] = pB;
	}
}

void printAns(int treeN, int caseN) {
	cout << "Case " << caseN << ": ";
	if (treeN == 1) cout << "There is one tree.\n";
	else if (treeN == 0) cout << "No trees.\n";
	else cout << "A forest of " << treeN << " trees.\n";
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int caseN = 1;
	while (1) {
		cin >> N >> M;
		if (N == 0 && M == 0) break;
		
		set(N);

		for (int i = 0, a, b; i < M; i++) {
			cin >> a >> b;

			if (find(a) == find(b)) { // 트리가 아닌 경우!
				checkCycle[a] = checkCycle[b] = true;
			}
			merge(a, b);
		}


		int treeN = 0;
		for (int i = 1; i <= N; i++){
			if (!visited[i]) {
				bool isCycle = false;
				for (int j = 1; j <= N; j++) {
					if (find(i) == find(j)) visited[j] = true;
					if (find(i) == find(j) && checkCycle[j]) isCycle = true;
				}
				if (!isCycle) treeN++;
			}
		}

		printAns(treeN, caseN);

		caseN++;
	}

	return 0;
}
