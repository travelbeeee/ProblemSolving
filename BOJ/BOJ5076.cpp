/*
	스택 문자파싱

	스택을 이용해 Open 태그를 담고
	Close 태그가 나타나면 stack의 top과 비교한다.
  
  1) < 를 발견하면 > 까지 안에 있는 keyword를 따온다.
  2) keyword가 열닫 태그라면 그냥 넘어가자
  3) 여는 태그라면 stack에 push한다
  4) 닫는 태그라면 stack의 pop과 비교한다. 
    --> 스택이 비어있거나 스택의 탑과 다르다면, illegal 한 상황 ( 짝이 없거나, 짝이 안맞는 경우 )
 */

#include<iostream>
#include<string>

#include<stack>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	string input;
	while (1) {
		getline(cin, input);

		if (input == "#") break;

		int ind = 0, len = input.length();
		stack<string> openTags;

		bool illegal = false;
		while (ind < len) {
			// 태그는 안에 속성값이 있거나 없거나
			// 속성값이있으면 띄어쓰기 하나 존재!
			// 없으면 그냥 쭉 가서 /> or >
			if (input[ind] == '<') {
				ind++;
        
				string tag = "";
				while (ind < len && input[ind] != '>') {
					tag.push_back(input[ind++]);
				}
        
				if (tag[tag.length() - 1] == '/') continue; // 열닫태크

				string realTag = "";
				for (int j = 0; j < tag.length(); j++) { // 띄어쓰기제거 --> 닫는태그에서는 속성이 없다 (HTML특성)
					if (tag[j] == ' ') break;
					realTag.push_back(tag[j]);
				}
        
				if (realTag[0] == '/') {// 닫는태그
					if (openTags.empty() || openTags.top() != realTag.substr(1)) {
						illegal = true;
						break;
					}
					openTags.pop();
				}
				else { // 여는태그
					openTags.push(realTag);
				}
			}
      
			ind++;
		}
		if (!openTags.empty()) illegal = true;

		if (illegal) cout << "illegal\n";
		else cout << "legal\n";
	}

	return 0;
}
