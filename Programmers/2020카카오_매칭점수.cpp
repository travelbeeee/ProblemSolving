/*
  시뮬레이션
  
  틀린 이유
  1)'word'를 단어 단위로 찾지 않아서 틀림.
  2) double 말고 int로 매칭점수 계산해서 틀림.
  
*/

#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(string word, vector<string> pages) {
    double basicScore[20] = {};
    vector<string> outerLink[20];
    map<string, int> page;
    // 일단 싹 다 소문자로 바꾸자.
    for (int i = 0; i < word.length(); i++) if ('A' <= word[i] && word[i] <= 'Z') word[i] = (word[i] - 'A') + 'a';
    for (int i = 0; i < pages.size(); i++)
        for (int j = 0; j < pages[i].length(); j++)
            if ('A' <= pages[i][j] && pages[i][j] <= 'Z') pages[i][j] = (pages[i][j] - 'A') + 'a';
    
    // i번 째 page의 URL, 기본점수, 외부링크를 따자.
    string urlTag = "<meta property=\"og:url\" content=";
    string aTag = "<a href=";
    for (int i = 0; i < pages.size(); i++) {
        for (int j = 0; j < pages[i].length(); j++) {
            // 자기 자신 URL 찾기
            if (j + urlTag.length() < pages[i].length() && pages[i].substr(j, urlTag.length()) == urlTag) {
                int k = j + urlTag.length() + 1;
                string url = "";
                while (pages[i][k] != '\"') {
                    url += pages[i][k];
                    k++;
                }
                page.insert({ url, i });
            }
            // Word 찾기
            if (0 < j && j + word.length() < pages[i].length() && pages[i].substr(j, word.length()) == word 
                && !('a' <= pages[i][j + word.length()] && pages[i][j + word.length()] <= 'z')
                && !('a' <= pages[i][j - 1] && pages[i][j - 1] <= 'z')) {
                basicScore[i] += 1.0;
            }
            // 외부 링크 찾기
            if (j + aTag.length() < pages[i].length() && pages[i].substr(j, aTag.length()) == aTag) {
                int k = j + aTag.length() + 1;
                string url = "";
                while (pages[i][k] != '\"') {
                    url += pages[i][k];
                    k++;
                }
                outerLink[i].push_back(url);
            }
        }
    }

    // i번 째 page의 외부링크를 통해 링크점수를 쌓아주자
    double linkScore[20] = {};
    for (int i = 0; i < pages.size(); i++) {
        for (int j = 0; j < outerLink[i].size(); j++) {
            // outerLink[i][j] 는 i번 째 url에서 j번 째 url로!
            // i번 째 페이지에서 있는 외부 링크가 존재하지않는 링크!
            if(page.find(outerLink[i][j]) == page.end()) continue;
            linkScore[page[outerLink[i][j]]] += ((double)basicScore[i] / (double)outerLink[i].size());
        }
    }
    double answer = 0.0;
    int ansInd = 0;
    for (int i = 0; i < pages.size(); i++) {
        if (answer < linkScore[i] + (double)basicScore[i]) {
            answer = linkScore[i] + (double)basicScore[i];
            ansInd = i;
        }
    }
    return ansInd;
}
