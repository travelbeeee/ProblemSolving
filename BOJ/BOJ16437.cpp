/*
	트리 위상정렬

	리프노드부터 시작해서 
	현재 노드까지 최대로 얻을 수 있는 양을
	부모 노드로 계속 올려준다.
*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int MAX_ISLAND = 123456;
int N;
long long island[MAX_ISLAND + 1];
int parent[MAX_ISLAND + 1];
int childCnt[MAX_ISLAND + 1];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int a, p;
	char t;

	cin >> N;
	for (int i = 2; i <= N; i++) {
		cin >> t >> a >> p;
		if (t == 'S') island[i] += a;
		else island[i] -= a;
		parent[i] = p;
		childCnt[p]++;
	}

	queue<int> leafNode;
	for (int i = 1; i <= N; i++)
		if (childCnt[i] == 0) leafNode.push(i);
	while (!leafNode.empty()) {
		int cur = leafNode.front();
		leafNode.pop();

		int next = parent[cur];
		childCnt[next]--;
		if (childCnt[next] == 0) leafNode.push(next);

		if (island[cur] <= 0) continue;
		island[next] += island[cur];
	}
	if (island[1] < 0) island[1] = 0;
	cout << island[1] << '\n';

	return 0;
}
