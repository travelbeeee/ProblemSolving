/*
  자료구조 Map을 이용해서 Cache저장소를 구현한다.
  
*/
#include <string>
#include <vector>
#include<map>

using namespace std;

int solution(int cacheSize, vector<string> cities) {
    if (cacheSize == 0) return 5 * cities.size();

    for (int i = 0; i < cities.size(); i++)
        for (int j = 0; j < cities[i].length(); j++)
            if ('A' <= cities[i][j] && cities[i][j] <= 'Z')
                cities[i][j] = (cities[i][j] - 'A') + 'a';

    int answer = 0;
    map<string, int> cache;

    for (int i = 0; i < cities.size(); i++) {
        // cache miss
        if (cache.find(cities[i]) == cache.end()) {
            answer += 5;
            if (cache.size() == cacheSize) {
                int ind = 99999999;
                string keyStr;
                for (auto it = cache.begin(); it != cache.end(); it++) {
                    if (it->second < ind) {
                        ind = it->second;
                        keyStr = it->first;
                    }
                }
                cache.erase(keyStr);
            }
            cache.insert({ cities[i], i });
        }
        else { // cache hit
            cache[cities[i]] = i;
            answer++;
        }
    }
    return answer;
}
