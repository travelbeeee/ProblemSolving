/**
 * 서로 변환할 수 있는 i번 째 string과 j번 째 string을 연결해주며
 * 그래프로 표현한 후, beginWord에서 endWord로 BFS 탐색을 진행한다.
 * 이때, 기존 경로를 저장하며 탐색을 진행한다.
 */

import java.util.*;

class Solution {
    int beginInd = 0, endInd= -1;
    DpBox[] dp = new DpBox[1001];

    public List<List<String>> findLadders(String beginWord, String endWord, List<String> wordList) {
        wordList.add(beginWord);
        List<List<Integer>> graph = new ArrayList<>(1001);
        List<List<String>> ans = new ArrayList<>();

        if (!wordList.contains(endWord)) return ans;

        settingGraph(graph, wordList, endWord);

        BFS(graph);

        if(dp[endInd].len == Integer.MAX_VALUE)
            return ans;
        reverseSearch(ans, endInd, Arrays.asList(wordList.get(endInd)), wordList);
        return ans;
    }

    private void reverseSearch(List<List<String>> ans, int curInd, List<String> strings, List<String> wordList) {
        if(curInd == beginInd){
            Collections.reverse(strings);
            ans.add(strings);
            return;
        }
        for (int next : dp[curInd].prev) {
            List<String> nextStrings = new ArrayList<>();
            nextStrings.addAll(strings);
            nextStrings.add(wordList.get(next));
            reverseSearch(ans, next, nextStrings, wordList);
        }
    }

    private void settingGraph(List<List<Integer>> graph, List<String> wordList, String endWord) {
        for (int i = 0; i < wordList.size(); i++) {
            graph.add(new ArrayList<>());
        }
        beginInd = wordList.size() - 1;
        for (int i = 0; i < wordList.size(); i++){
            if(wordList.get(i).equals(endWord)){
                endInd = i;
            }
            for (int j = i + 1; j < wordList.size(); j++){
                if(canTransformation(wordList.get(i), wordList.get(j))){
                    graph.get(i).add(j);
                    graph.get(j).add(i);
                }
            }
        }
        for (int i = 0; i < wordList.size(); i++) {
            dp[i] = new DpBox(Integer.MAX_VALUE, new ArrayList<>());
        }
    }

    private void BFS(List<List<Integer>> graph) {
        Queue<BfsBox> q = new LinkedList<>();
        q.add(new BfsBox(beginInd, 0));
        dp[beginInd].len = 0;
        while (!q.isEmpty()) {
            BfsBox cur = q.poll();
            if(cur.curNode == endInd){
                break;
            }
            for (Integer next : graph.get(cur.curNode)){
                if (cur.len + 1 < dp[next].len){
                    dp[next].len = cur.len + 1;
                    ArrayList<Integer> prev = new ArrayList<>();
                    prev.add(cur.curNode);
                    dp[next].prev = prev;
                    q.add(new BfsBox(next, cur.len + 1));
                }
                else if (cur.len + 1 == dp[next].len){
                    dp[next].prev.add(cur.curNode);
                }
            }
        }
    }

    // 둘이 한 글자만 다르면 OK!
    private boolean canTransformation(String str1, String str2) {
        if(str1.length() != str2.length()) return false;
        boolean isDiff = false;
        for(int i = 0; i < str1.length(); i++){
            if(str1.charAt(i) != str2.charAt(i)){
                if(isDiff)
                    return false;
                isDiff = true;
            }
        }
        return true;
    }

    private class DpBox {
        int len;
        List<Integer> prev;

        public DpBox(int len, List<Integer> prev) {
            this.len = len;
            this.prev = prev;
        }
    }

    private class BfsBox {
        int curNode, len;

        public BfsBox(int curNode, int len) {
            this.curNode = curNode;
            this.len = len;
        }
    }
}
