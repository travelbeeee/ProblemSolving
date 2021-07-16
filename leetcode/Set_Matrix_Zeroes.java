import java.util.ArrayList;
import java.util.List;

class Solution {
    public void setZeroes(int[][] matrix) {
        List<Integer> rows = new ArrayList<>();
        List<Integer> cols = new ArrayList<>();
        for(int row = 0; row < matrix.length; row++){
            for(int col = 0; col < matrix[0].length; col++){
                if(matrix[row][col] == 0){
                    rows.add(row);
                    cols.add(col);
                }
            }
        }
        for (Integer row : rows) {
            for(int col = 0; col < matrix[row].length; col++)
                matrix[row][col] = 0;
        }
        for (Integer col : cols) {
            for (int row = 0; row < matrix.length; row++)
                matrix[row][col] = 0;
        }
    }
}
