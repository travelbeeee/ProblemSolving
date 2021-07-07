import java.util.*;

class Solution {
    /**
     * 단순하게 풀기
     */
    public int minSetSize1(int[] arr){
        int N = arr.length;
        Integer[] countList = new Integer[100001];
        for(int i = 0; i < 100001; i++) countList[i] = 0;

        for (int i = 0; i < N; i++)
            countList[arr[i]]++;

        Arrays.sort(countList, Comparator.reverseOrder());

        int ind = 0, res = 0, goal = N / 2;
        while(goal > 0){
            goal -= countList[ind];
            ind++;
            res++;
        }
        return res;
    }

    /**
     * 자료구조를 이용해서 같은 상황을 해결하기
     */
    public int minSetSize2(int[] arr) {
        int N = arr.length;
        int goal = N / 2;
        Map<Integer, Integer> m = new HashMap<>();
        PriorityQueue<Pair> pq = new PriorityQueue<Pair>(new Comparator<Pair>() {
            @Override
            public int compare(Pair o1, Pair o2) {
                if (o1.count > o2.count) return -1;
                else if (o1.count < o2.count) return 1;
                return 0;
            }
        });

        for (int i = 0; i < N; i++){
            if(m.containsKey(arr[i])){
                Integer value = m.get(arr[i]);
                m.replace(arr[i], value + 1);
            }
            else{
                m.put(arr[i], 1);
            }
        }

        for (Integer key : m.keySet()) {
            pq.add(new Pair(key, m.get(key)));
        }

        int res = 0, removed = 0;
        while(removed < goal){
            Pair cur = pq.poll();
            removed += cur.count;
            res++;
        }
        return res;
    }

    private class Pair {
        Integer value, count;

        public Pair(Integer value, Integer count) {
            this.value = value;
            this.count = count;
        }
    }
}
