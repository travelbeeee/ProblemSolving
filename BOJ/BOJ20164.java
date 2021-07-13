/*
    자바 substring 은 C++이랑 다르게 beginIndex ~ endIndex !!
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String N = br.readLine();

        Queue<Bfs> q = new LinkedList<>();
        q.add(new Bfs(N, countOddN(N)));
        int maxN = -1, minN = 99999999;
        while (!q.isEmpty()) {
            Bfs cur = q.poll();
            int len = cur.str.length();
            if(len == 1){
                maxN = Math.max(maxN, cur.oddCnt);
                minN = Math.min(minN, cur.oddCnt);
            }
            else if (len == 2){
                String nextS = Integer.toString(cur.str.charAt(0) - '0' + cur.str.charAt(1) - '0');
                q.add(new Bfs(nextS, cur.oddCnt + countOddN(nextS)));
            }
            else if (len >= 3){
                for (int i = 1; i < len - 1; i++) {
                    for (int j = i + 1; j < len; j++) {
                        String nextS = Integer.toString(
                                Integer.parseInt(cur.str.substring(0, i)) + Integer.parseInt(cur.str.substring(i, j)) + Integer.parseInt(cur.str.substring(j))
                        );
                        q.add(new Bfs(nextS, cur.oddCnt + countOddN(nextS)));
                    }
                }
            }
        }

        System.out.println(minN + " " + maxN);

        return;
    }

    private static int countOddN(String n){
        int oddN = 0;
        for(int i = 0; i < n.length(); i++){
            if((n.charAt(i) - '0') % 2 == 1) oddN++;
        }
        return oddN;
    }

    static class Bfs{
        String str;
        int oddCnt;

        public Bfs(String curN, int curOddCnt) {
            this.str = curN;
            this.oddCnt = curOddCnt;
        }
    }
}
