/*
  Map Union-Find
  
  자료구조 Map을 이용해서 map{i, j} 는 i방을 원하는 사람은 j를 배정해줘야된다! 라고 정의한다.
  
  Union Find의 Find 함수를 이용해서 트리를 단축시키면 시간 초과 문제를 해결할 수 있다.
  `return m.find(cur)->second = find(m.find(cur)->second);`
*/
#include <vector>
#include <map>

using namespace std;

map<long long, long long> m;

long long find(long long cur){
    if(m.find(cur) == m.end()) return cur;
    return m.find(cur)->second = find(m.find(cur)->second);
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    m.clear();
    
    for (int i = 0; i < room_number.size(); i++) {
        long long roomNumber = find(room_number[i]);
        answer.push_back(roomNumber);
        m.insert({roomNumber, roomNumber + 1});
    }
    return answer;
}
