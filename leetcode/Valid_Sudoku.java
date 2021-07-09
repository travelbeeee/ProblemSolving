/**
 * Sudoku 보드판을 행 / 열 / 박스별로 체크한다.
 */
class Solution {
    public boolean isValidSudoku(char[][] board) {
        if(!checkRow(board, 9, 9)) return false;
        if(!checkCol(board, 9, 9)) return false;
        if(!checkBox(board, 9, 9, 3)) return false;
        return true;
    }

    private boolean checkBox(char[][] board, int row, int col, int boxSize) {
        for (int i = 0; i < row; i += boxSize){
            for (int j = 0; j < col; j += boxSize) {
                boolean[] visited = new boolean[10];
                for (int x = 0; x < boxSize; x++)
                    for(int y = 0; y < boxSize; y++){
                        if (board[i + x][j + y] == '.') continue;
                        if (visited[board[i + x][j + y] - '0']) return false;
                        visited[board[i + x][j + y] - '0'] = true;
                    }
            }
        }
        return true;
    }

    private boolean checkCol(char[][] board, int row, int col) {
        for (int j = 0; j < col; j++){
            boolean[] visited = new boolean[10];
            for(int i = 0; i < row; i++){
                if(board[i][j] == '.') continue;
                if(visited[board[i][j] - '0']) return false;
                visited[board[i][j] - '0'] = true;
            }
        }
        return true;
    }

    private boolean checkRow(char[][] board, int row, int col) {
        for(int i = 0; i < row; i++){
            boolean[] visited = new boolean[10];
            for (int j = 0; j < col; j++){
                if(board[i][j] == '.') continue;
                if(visited[board[i][j] - '0']) return false;
                visited[board[i][j] - '0'] = true;
            }
        }
        return true;
    }
}
