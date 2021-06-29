import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
    static int N, M, K;
    static String[] tile = new String[10];
    static Map<String, Integer> godStrMap = new HashMap<>();

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] numS = br.readLine().split(" ");
        N = Integer.parseInt(numS[0]);
        M = Integer.parseInt(numS[1]);
        K = Integer.parseInt(numS[2]);
        for (int i = 0; i < N; i++){
            tile[i] = br.readLine();
        }

        makeAllPermutation();

        for (int i = 0; i < K; i++){
            String str = br.readLine();
            if(godStrMap.containsKey(str)) System.out.println(godStrMap.get(str));
            else System.out.println(0);
        }
        br.close();

        return;
    }

    private static void makeAllPermutation() {
        for (int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                BFS(i, j);
            }
        }
    }

    private static void BFS(int x, int y) {
        int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        Queue<Box> q = new LinkedList<>();

        StringBuilder curS = new StringBuilder();
        curS.append(tile[x].charAt(y));

        q.add(new Box(x, y, curS));

        if(!godStrMap.containsKey(curS.toString())) godStrMap.put(curS.toString(), 1);
        else godStrMap.replace(curS.toString(), godStrMap.get(curS.toString()) + 1);

        for (int l = 1; l < 5; l++){
            int size = q.size();
            for (int s = 0; s < size; s++){
                Box cur = q.poll();
                for (int d = 0; d < 8; d++){
                    int nextX = cur.curX + dx[d], nextY = cur.curY + dy[d];
                    if(nextX == -1) nextX = N - 1;
                    else if (nextX == N) nextX = 0;
                    if (nextY == -1) nextY = M - 1;
                    else if (nextY == M) nextY = 0;

                    StringBuilder nextS = new StringBuilder();
                    nextS.append(cur.curS.toString());
                    nextS.append(tile[nextX].charAt(nextY));
                    q.add(new Box(nextX, nextY, nextS));
                    if(!godStrMap.containsKey(nextS.toString())) godStrMap.put(nextS.toString(), 1);
                    else godStrMap.replace(nextS.toString(), godStrMap.get(nextS.toString()) + 1);

                }
            }
        }
    }

    static class Box {
        int curX, curY;
        StringBuilder curS;

        public Box(int curX, int curY, StringBuilder curS) {
            this.curX = curX;
            this.curY = curY;
            this.curS = curS;
        }
    }
}
