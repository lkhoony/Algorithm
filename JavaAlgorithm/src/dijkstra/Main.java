package dijkstra;
import java.util.*;

public class Main {
	
	public static final int INF=99999;
	public static ArrayList<ArrayList<Point>> list;
	
	public static class Point implements Comparable<Point>{
		
		int dest;
		int weight;
		
		public Point(int dest, int weight) {
			this.dest = dest;
			this.weight = weight;
		}
		
		@Override
		public int compareTo(Point o) {
			if(this.weight<o.weight) {
				return -1;
			}else if(this.weight>o.weight) {
				return 1;
			}else {
				return 0;
			}
		}
	}
	
	public static void main(String[] args) {
		
		int nV, nE, origin, dest, weight, weightSum=0;
		Scanner scan = new Scanner(System.in);
		boolean[] visit;
		int[] dist;
		
		nV = scan.nextInt();
		nE = scan.nextInt();
		
		list = new ArrayList<ArrayList<Point>>();
		visit = new boolean[nV+1];
		dist = new int[nV+1];
		
		// dist 배열을 INF로 채우기
		Arrays.fill(dist, INF);
		
		for(int i=0;i<=nV;i++) {
			list.add(new ArrayList<Point>());
		}
		
		for(int i=0;i<nE;i++) {
			
			origin = scan.nextInt();
			dest = scan.nextInt();
			weight = scan.nextInt();
			
			list.get(origin).add(new Point(dest,weight));
			list.get(dest).add(new Point(origin,weight));
			
		}
		
		PriorityQueue<Point> pq = new PriorityQueue<Point>();
		
		pq.add(new Point(1,0));
		dist[1] = 0;
		
		while(!pq.isEmpty()) {
			
			Point curPoint = pq.poll();
			int curVertex = curPoint.dest;
			int curWeight = curPoint.weight;
			
			if(visit[curVertex]) {
				continue;
			}
			
			visit[curVertex] = true;
			
			for(int i=0;i<list.get(curVertex).size();i++) {
				int nextVertex = list.get(curVertex).get(i).dest;
				int nextWeight = list.get(curVertex).get(i).weight;
				
				if(!visit[nextVertex] && nextWeight + curWeight < dist[nextVertex]) {
					dist[nextVertex] = curWeight + nextWeight;
					pq.add(new Point(nextVertex,dist[nextVertex]));
				}
				
			}
			
		}
		
		for(int i=1;i<dist.length;i++) {
			System.out.println(dist[i]);
		}
		
	}

}

/*
6 9
1 2 8
1 3 2
1 4 4
2 3 7
2 5 2
3 4 1
3 5 3
3 6 9
4 6 5 

*/