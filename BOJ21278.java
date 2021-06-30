/*
    자바 substring 은 C++이랑 다르게 beginIndex ~ endIndex !!
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

class Main {
    static int INF = 99999999;
    static int N, M, A, B;
    static int[][] dist = new int[101][101];
    static int store1 = -1, store2 = -1, timeSum = INF;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String[] s = br.readLine().split(" ");
        N = Integer.parseInt(s[0]);
        M = Integer.parseInt(s[1]);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                dist[i][j] = INF;
        for (int i = 1; i <= N; i++)
            dist[i][i] = 0;

        for (int i = 0; i < M; i++){
            s = br.readLine().split(" ");
            A = Integer.parseInt(s[0]);
            B = Integer.parseInt(s[1]);
            dist[A][B] = 1;
            dist[B][A] = 1;
        }

        // floydwarshall
        floydWarshall();

        buildChickenStore();

        System.out.println(store1 + " " + store2 + " " + 2 * timeSum);

        return;
    }

    private static void buildChickenStore() {
        for (int i = 1; i <= N; i++){ // i, j에 치킨집을 지음
            for(int j = i + 1; j <= N; j++){
                int tempSum = 0;
                for (int k = 1; k <= N; k++)
                    tempSum += Math.min(dist[k][i], dist[k][j]);
                if(tempSum < timeSum){
                    timeSum = tempSum;
                    store1 = i;
                    store2 = j;
                }
            }
        }
    }

    private static void floydWarshall() {
        for (int k = 1; k <= N; k++){
            for (int i = 1; i <= N; i++){
                for(int j = 1; j <= N; j++){
                    if(dist[i][k] + dist[k][j] <= dist[i][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

}
