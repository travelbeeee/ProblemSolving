/*
	구현

	1) OPcard = { 카드번호, 명령, 넘버 } deque로 관리
	2) 개인공간숫자들 = { 숫자번호, 친구번호 } map으로 관리
*/
#include<iostream>
#include<map>
#include<string>
#include<queue>

using namespace std;

struct opCard {
	int cardNum;
	string order;
	int n;
};

int N, T, turn[500000];
deque<opCard> opCardList;
opCard peopleCardList[500001];
bool peopleHaveCard[500001];
map<int, int> privateSpace;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int cardNum, n = 0;
	string input, order;
	cin >> N >> T;
	for (int i = 0; i < T; i++)
		cin >> turn[i];

	for (int i = 0; i < T; i++) {
		cin >> cardNum >> order;
		if (order != "next")
			cin >> n;
		else
			n = 0;
		opCardList.push_back({ cardNum, order, n });
	}

	// T턴에 걸쳐 게임을 진행해보자.
	for (int i = 0; i < T; i++) {
		// turn[i] 사람의 차례!
		if (peopleHaveCard[turn[i]]) { // acquire가 남아있음
			cout << peopleCardList[turn[i]].cardNum << '\n';

			// acquire 성공!
			int goalN = peopleCardList[turn[i]].n;
			if (privateSpace.find(goalN) == privateSpace.end()) {
				privateSpace.insert({ goalN, turn[i] });
				peopleHaveCard[turn[i]] = false;
			}
		}
		else { // 가지고 있는 카드가 없음
			opCard curCard = opCardList.front();
			opCardList.pop_front();

			cout << curCard.cardNum << '\n';

			if (curCard.order == "next") continue;
			else if (curCard.order == "release") {
				privateSpace.erase(curCard.n);
			}
			else {
				if (privateSpace.find(curCard.n) == privateSpace.end()) {
					privateSpace.insert({ curCard.n, turn[i] });
				}
				else {
					peopleHaveCard[turn[i]] = true;
					peopleCardList[turn[i]] = curCard;
				}
			}
		}
	}
	return 0;
}
