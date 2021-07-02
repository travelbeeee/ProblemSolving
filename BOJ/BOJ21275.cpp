/*
  BigInteger를 사용해야된다!
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");

        String A = input[0];
        String B = input[1];

        // 2 ~ 36진법 중에 하나!
        BigInteger[][] changeResult = new BigInteger[2][37];
        for (int i = 2; i <= 36; i++){
            changeResult[0][i] = getBaseNotation(A, i);
        }
        for (int i = 2; i <= 36; i++){
            changeResult[1][i] = getBaseNotation(B, i);
        }

        List<Ans> ans = new ArrayList<>();
        for (int i = 2; i <= 36; i++){
            for(int j = 2; j <= 36; j++){
                if(i == j || changeResult[0][i].compareTo(BigInteger.valueOf(0L)) == -1
                || changeResult[1][j].compareTo(BigInteger.valueOf(0L)) == -1
                || changeResult[0][i].compareTo(new BigInteger("9223372036854775807")) == 1
                || changeResult[1][j].compareTo(new BigInteger("9223372036854775807")) == 1)
                    continue;

                if(changeResult[0][i].compareTo(changeResult[1][j]) == 0){ // 정답 케이스
                    ans.add(new Ans(changeResult[0][i], i, j));
                }
            }
        }
        if(ans.isEmpty()){
            System.out.println("Impossible");
        }
        else if (ans.size() >= 2){
            System.out.println("Multiple");
        }
        else{
            System.out.println(ans.get(0).X + " " + ans.get(0).A + " " + ans.get(0).B);
        }
    }

    private static BigInteger getBaseNotation(String str, int r) {
        for (int i = 0; i < str.length(); i++){
            if(r <= changeNumber(str.charAt(i)))
                return new BigInteger("-1");
        }
        BigInteger res = BigInteger.valueOf(0L);
        BigInteger m = BigInteger.valueOf(1L);

        for (int i = str.length() - 1; i >= 0; i--){
            res = res.add(BigInteger.valueOf(1L * changeNumber(str.charAt(i))).multiply(m));
            m = m.multiply(BigInteger.valueOf(1L * r));
        }
        return res;
    }

    private static int changeNumber(char charAt) {
        if('0' <= charAt && charAt <= '9')
            return (charAt - '0');
        return (charAt - 'a') + 10;
    }


    private static class Ans {
        private BigInteger X;
        private Integer A, B;
        public Ans(BigInteger x, Integer a, Integer b) {
            X = x;
            A = a;
            B = b;
        }
    }
}
