/*
  BFS 완전탐색
  
  입력된 문장을 앞에서부터 BFS탐색으로 
  현재 탐색 지점부터 가능한 모든 word들을 이용해 탐색해본다.
  { 어디부터 탐색 해야되는지, cost가 얼마나 들었는지 }
  2개 값을 이용한다.
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

const int INF = 9999999;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int S, N;
	string s, word;
	vector<string> wordList;

	cin >> s >> N;
	for (int i = 0; i < N; i++) {
		cin >> word;
		wordList.push_back(word);
	}

	queue<pair<int, int>> q; // { N의 어디부터 탐색해야되는지, cost }
	int ans = INF, visited[51];
	for (int i = 0; i < 51; i++) 
		visited[i] = INF;

	q.push({ 0, 0 }); 
	visited[0] = 0;
	while (!q.empty()) {
		int ind = q.front().first;
		int cost = q.front().second;
		q.pop();

		if (ind == s.length()) {
			ans = min(ans, cost);
			continue;
		}
		if (visited[ind] < cost) continue;

		for (int i = 0; i < N; i++) {
			if (ind + wordList[i].length() - 1 >= s.length()) continue;
			// s[ind] 부터 wordList[i] 랑 비교해보자.
			int alpS[26] = {}, alpWord[26] = {};
			for (int j = 0; j < wordList[i].length(); j++) {
				alpS[s[ind + j] - 'a']++;
				alpWord[wordList[i][j] - 'a']++;
			}

			// wordList[i]로 만들 수 없는 부분
			bool isPossible = true;
			for (int j = 0; j < 26; j++) 
				if (alpS[j] != alpWord[j]) isPossible = false;
			if (!isPossible) continue;

			int c = 0;
			for (int j = 0; j < wordList[i].length(); j++)
				if (wordList[i][j] != s[ind + j])
					c++;
          
			int nextInd = ind + wordList[i].length();
			int nextCost = cost + c;
			if (nextCost < visited[nextInd]) {
				q.push({ nextInd, nextCost });
				visited[nextInd] = nextCost;
			}
		}
	}

	if (ans == INF) ans = -1;
	cout << ans << '\n';

	return 0;
}
