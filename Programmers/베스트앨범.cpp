/*
  우선순위큐와 맵을 이용해서 구현하면 된다.
*/
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

vector<int> solution(vector<string> genres, vector<int> plays) {
    // 장르별로 Map을 이용해 번호를 부여해주자!
    map<string, int> genreMap;
    int genreInd = 0;
    for (int i = 0; i < genres.size(); i++) {
        if (genreMap.find(genres[i]) == genreMap.end())
            genreMap.insert({ genres[i], genreInd++ });
    }
    int genreSum[100] = {}; // genreSum[i] := i번 째 장르 총 play횟수
    priority_queue<pair<int, int>> genrePlay[100]; // genrePlay[i] := i번 째 장르 (곡 play횟수, 곡 번호)
    for (int i = 0; i < genres.size(); i++) {
        genreSum[genreMap[genres[i]]] += plays[i];
        genrePlay[genreMap[genres[i]]].push({ plays[i], -i });
    }
    
    // (i번 째 장르, 총 play 횟수)
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < genreInd; i++)
        pq.push({ genreSum[i], i });

    vector<int> answer;
    while (!pq.empty()) {
        int curGenre = pq.top().second;
        pq.pop();

        answer.push_back(-genrePlay[curGenre].top().second);
        genrePlay[curGenre].pop();
        if (genrePlay[curGenre].empty()) continue;
        answer.push_back(-genrePlay[curGenre].top().second);
        genrePlay[curGenre].pop();
    }
    return answer;
}
