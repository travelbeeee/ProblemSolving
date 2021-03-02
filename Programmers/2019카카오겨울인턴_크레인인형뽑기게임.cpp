/*
  
*/
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int N = board.size(), answer = 0;
    vector<int> basket;
    for (int k = 0; k < moves.size(); k++){
        int move = moves[k] - 1, i = 0;
        while(i <= N - 1&& board[i][move] == 0)
            i++;
        if(i <= N - 1){
            basket.push_back(board[i][move]);
            board[i][move] = 0;
        }
        if(basket.size() >= 2 && basket[basket.size() - 1] == basket[basket.size() - 2]){
            answer += 2;
            basket.pop_back();
            basket.pop_back();
        }
    }
    return answer;
}
