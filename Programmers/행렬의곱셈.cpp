#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
    vector<vector<int>> answer;
    int arr1Row = arr1.size(), arr1Col = arr1[0].size();
    int arr2Row = arr2.size(), arr2Col = arr2[0].size();
    for (int i = 0; i < arr1Row; i++){
        vector<int> newArrRow;
        for (int j = 0; j < arr2Col; j++){
            int sum = 0;
            for (int k = 0; k < arr1Col; k++)
                sum += arr1[i][k] * arr2[k][j];
            newArrRow.push_back(sum);
        }
        answer.push_back(newArrRow);
    }
    return answer;
}
