/*
  입력된 S를 전처리해 모든 튜플로 변환한다.
  튜플 크기가 1인 것부터 시작해서 answer에 하나하나 찾아서 넣는다.
*/
#include <string>
#include <vector>
#include<iostream>

using namespace std;

vector<int> solution(string s) {
    vector<vector<int>> tuples;
    vector<int> tuple;
    string temp = "";
    int N = s.length();
    for (int i = 1; i < N - 1; i++){
        if(s[i] == '{' || (s[i] == ',' && s[i - 1] == '}')) continue;
        
        if(s[i] == ','){
            tuple.push_back(stoi(temp));
            temp = "";
        }
        else if (s[i] == '}'){
            tuple.push_back(stoi(temp));
            tuples.push_back(tuple);
            tuple.clear();
            temp="";
        }
        else
            temp += s[i];
    }
    vector<int> answer;
    for (int i = 1; i <= tuples.size(); i++){
        for (int j = 0; j < tuples.size(); j++){
            if(tuples[j].size() == i){ 
                // tuples[j] 에 들어가있는 애들 중 answer에 없는애들을 추가하자
                for (int k = 0; k < tuples[j].size(); k++){
                    bool check = true;
                    for(int l = 0; l < answer.size(); l++){
                        if(tuples[j][k] == answer[l]) check = false;
                    }
                    if(check) answer.push_back(tuples[j][k]);
                }
            }
        }
    }
    return answer;
}
