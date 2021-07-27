/*
* 백트레킹
*/
import java.util.ArrayList;
import java.util.List;

class Solution {
    public String emptyRow = "";

    public List<List<String>> solveNQueens(int n) {
        setEmptyRow(n);

        List<List<String>> res = new ArrayList<>();

        BFS(new ArrayList<String>(), n, res);

        return res;
    }

    private void setEmptyRow(int n) {
        StringBuilder row = new StringBuilder();
        for(int i = 0; i < n; i++)
            row.append('.');
        emptyRow = row.toString();
    }

    private void BFS(List<String> map, int n, List<List<String>> res) {
        if(map.size() == n){
            ArrayList<String> finishMap = new ArrayList<String>();
            finishMap.addAll(map);
            res.add(finishMap);
            return;
        }
        // map.size() 번 째 row를 만들어야된다!
        StringBuilder row = new StringBuilder(emptyRow);
        for(int j = 0; j < n; j++){
            if(canPutQueen(map, j, n)){
                row.setCharAt(j, 'Q');
                map.add(row.toString());
                BFS(map, n, res);
                map.remove(map.size() - 1);
                row.setCharAt(j, '.');
            }
        }
    }

    private boolean canPutQueen(List<String> map, int j, int n) {
        int newRow = map.size();
        for(int i = 0; i < map.size(); i++){
            if(map.get(i).charAt(j) == 'Q') return false;
            if(j + (newRow - i) < n && map.get(i).charAt(j + (newRow - i)) == 'Q') return false;
            if(j - (newRow - i) >= 0 && map.get(i).charAt(j - (newRow -i)) == 'Q') return false;
        }
        return true;
    }
}
