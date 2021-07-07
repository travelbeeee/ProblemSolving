import java.util.ArrayList;
import java.util.List;

class Solution {
    public String convert(String s, int numRows) {
        if(numRows == 1) return s;

        List<StringBuilder> map = new ArrayList<>();
        for (int i = 0; i < numRows; i++){
            map.add(new StringBuilder());
        }
        int x = 0, dir = 0;
        int[] dx = {1, -1};

        int sInd = 0, jump = 0;
        while(sInd < s.length()) {
            map.get(x).append(s.charAt(sInd));
            x += dx[dir];
            jump++;
            sInd++;
            if(jump == numRows - 1){
                jump = 0;
                dir = (dir + 1) % 2;
            }
        }

        StringBuilder ans = new StringBuilder();
        for (int i = 0; i < map.size(); i++)
            ans.append(map.get(i));
        return ans.toString();
    }
}
