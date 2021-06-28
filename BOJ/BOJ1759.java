import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;

public class Main {

    static int L, C;
    static String[] alp;
    static ArrayList<String> cipher = new ArrayList<>();

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] numIn = br.readLine().split(" ");
        alp = br.readLine().split(" ");
        br.close();

        L = Integer.parseInt(numIn[0]);
        C = Integer.parseInt(numIn[1]);

        Arrays.sort(alp);

        backtracking(0, 0);

        return;
    }

    private static boolean isVowel(String s){
        char c = s.charAt(0);
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return true;
        return false;
    }
  
    private static void backtracking(int startInd, int len) {
        if(len == L){
            int consonant = 0, vowel = 0;
            for (String s : cipher) {
                if(isVowel(s)) vowel++;
                else consonant++;
            }
            if(!(1 <= vowel && 2 <= consonant)) return;
            for (String s : cipher) {
                System.out.print(s);
            }
            System.out.println();
            return;
        }
        for (int i = startInd; i < C; i++){
            cipher.add(alp[i]);
            backtracking(i + 1, len + 1);
            cipher.remove(cipher.size() - 1);
        }
    }
}
