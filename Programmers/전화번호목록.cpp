/*
  Input 글자 수 크기가 1 ~ 20 이고, 글자수가 더 큰 String은 더 작은 String의 접두사가 될 수 없으므로
  복잡도를 낮추기 위해 글자수 별로 따로 Map에 담아두고
  글자수가 큰 친구들의 접두사를 substr 해서 확인해본다.
*/
#include <string>
#include <vector>
#include <map>

using namespace std;

bool solution(vector<string> phone_book) {
	map<string, bool> m[21];
	for (int i = 0; i < phone_book.size(); i++)
		m[(int)phone_book[i].length()].insert({ phone_book[i], true });

	for (int i = 20; i >= 1; i--) {
		if (m[i].empty()) continue;
		for (int j = i - 1; j >= 1; j--) {
			if (m[j].empty()) continue;
			// m[i]에 있는 애들의 앞 j글자씩 접두사를 떼서 확인해보자!
			for (auto it = m[i].begin(); it != m[i].end(); it++) {
				if (m[j].find(it->first.substr(0, j)) != m[j].end()) return false;
			}
		}
	}
	return true;
}
