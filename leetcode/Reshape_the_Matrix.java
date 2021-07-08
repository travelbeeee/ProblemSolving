class Solution {
    public int[][] matrixReshape(int[][] mat, int r, int c) {
        int N = mat.length;
        int M= mat[0].length;

        if(N * M != r * c) {
            return mat;
        }

        return reshape(mat, N, M, r, c);
    }

    private int[][] reshape(int[][] mat, int n, int m, int r, int c) {
        int x = 0, y = 0;
        int[][] reshapeMat = new int[r][c];
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                reshapeMat[x][y] = mat[i][j];
                y++;
                if(y == c){
                    x++;
                    y = 0;
                }
            }
        }
        return reshapeMat;
    }
}
