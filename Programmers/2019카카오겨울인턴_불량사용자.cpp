/*
  backtracking
  
  1) user_id에서 banned_id만큼 모든 경우를 뽑아본다.
  2) 뽑은 경우가 banned_id랑 매치가 되는 경우라면
    sort 후 지금까지 정답이었던 사례들과 비교해서 
    처음 입력되는 사례라면 push해준다.
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// user_id에서 banned_id만큼 모든 경우를 뽑아보자.
vector<vector<int>> answer;
vector<int> mapping;
bool visited[8];

void init(void){
    answer.clear();
    mapping.clear();
    for (int i = 0; i < 8; i++) visited[i] = false;
}

void backtracking(vector<string> user_id, vector<string> banned_id){
    if(mapping.size() == (int)banned_id.size()){
        for (int i = 0; i < (int)banned_id.size(); i++){
            if(user_id[mapping[i]].length() != banned_id[i].length())
                return;
        }
        for (int i = 0; i < (int)banned_id.size(); i++){
            for (int j = 0; j < banned_id[i].length(); j++){
                if(banned_id[i][j] != '*' && user_id[mapping[i]][j] != banned_id[i][j])
                    return;
            }
        }
        vector<int> temp = mapping;
        sort(temp.begin(), temp.end());
        bool isDuplicated = false;
        for (int i = 0; i < answer.size(); i++) {
            bool check = true;
            for (int j = 0; j < answer[i].size(); j++)
                if (answer[i][j] != temp[j])
                    check = false;
            if (check)
                isDuplicated = true;
        }
        if (!isDuplicated) 
            answer.push_back(temp); 
        return;
    }
    
    for(int i = 0; i < (int)user_id.size(); i++){
        if(!visited[i]){
            mapping.push_back(i);
            visited[i] = true;
            backtracking(user_id, banned_id);
            visited[i] = false;
            mapping.pop_back();
        }
    }
    
}

int solution(vector<string> user_id, vector<string> banned_id) {
    
    init();
    
    backtracking(user_id, banned_id);
    
    return (int)answer.size();;
}
