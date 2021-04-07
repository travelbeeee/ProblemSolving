/*
  내풀이
  1) 라인스위핑을 이용해서 도로 In / 도로 Out 을 먼저 들어온 순서대로 접근한다!
  2) 아직 카메라를 설치해서 checked 되지 않았는데 도로 Out 차례가 온 Car는 카메라를 설치해서 잡아야되므로
    그 위치에 카메라를 설치해 지금까지 In 해버린 모든 Car 까지 한 꺼번에 잡아버린다.
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<vector<int>> routes) {
    int answer = 0;
    bool checked[10000] = {};
    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i < routes.size(); i++) {
        pq.push({ -routes[i][0], {1, i} });
        pq.push({ -routes[i][1], {-1, i} });
    }

    vector<int> inCar;
    while (!pq.empty()) {
        int dist = -pq.top().first;
        int dir = pq.top().second.first;
        int ind = pq.top().second.second;
        pq.pop();
        if (dir == 1) { // IN
            inCar.push_back(ind);
        }
        else { // OUT
            if (!checked[ind]) {// 카메라를 여기다가 설치!!
                for (int i = 0; i < inCar.size(); i++)
                    checked[inCar[i]] = true;
                inCar.clear();
                answer++;
            }
        }
    }
    return answer;
}

/*
  이재권님 풀이
  
  Out이 빠르고, In이 빠른 차부터 차례대로 해당 위치(limit)에 카메라를 설치했다고 생각하고
  limit 보다 먼저 들어온 차들은 그냥 자동 check...!!
  훨씬 깔끔한 풀이...
  
  #include <bits/stdc++.h>

  using namespace std;

  bool cmp(vector<int> a, vector<int> b) { return a[1] < b[1]; }

  int solution(vector<vector<int>> routes) {
      int answer = 0;
      int limit = -30001;
      sort(routes.begin(), routes.end(), cmp);
      for(int i = 0; i < routes.size(); i++){
          if(limit < routes[i][0]){
              answer++;
              limit = routes[i][1];
          }
      }
      return answer;
  }
*/
