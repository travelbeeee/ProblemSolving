class Solution {
    public String countAndSay(int n) {
        String str = "1";
        for (int i = 1; i < n; i++)
            str = changeDigitString(str);
        return str;
    }

    private String changeDigitString(String str) {
        int ind = 0;
        StringBuilder changedStr = new StringBuilder();
        while (ind < str.length()) {
            int cnt = 1;
            while(ind + 1 < str.length() && str.charAt(ind) == str.charAt(ind + 1)){
                ind++;
                cnt++;
            }
            // str[ind]가 cnt개 등장
            changedStr.append(cnt);
            changedStr.append(str.charAt(ind));
            ind++;
        }
        return changedStr.toString();
    }
}
