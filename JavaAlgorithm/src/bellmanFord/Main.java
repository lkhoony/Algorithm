package bellmanFord;
import java.util.*;

public class Main {
	
	public static int INF = Integer.MAX_VALUE;
	
	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		int nV, nE, origin, dest, weight;
		ArrayList<Edge> edgeList;
		int[] dist;
		boolean flag = false;
		
		nV = scan.nextInt();
		nE = scan.nextInt();
		
		edgeList = new ArrayList<Edge>(nE);
		dist = new int[nV+1];
		
		for(int i=0;i<nE;i++) {
			origin = scan.nextInt();
			dest = scan.nextInt();
			weight = scan.nextInt();
			
			edgeList.add(new Edge(origin,dest,weight));
		}
		
		// bellman ford
		Arrays.fill(dist, INF);
		dist[1] = 0;
		
		// nV-1회 업데이트 후 nV번 째에 음의 순환 검사
		for(int i=0;i<nV;i++) {
			
			flag = false;
			
			for(int j=0;j<edgeList.size();j++) {
				
				if(dist[edgeList.get(j).origin]==INF) {
					continue;
				}
				
				if(dist[edgeList.get(j).origin] + edgeList.get(j).weight < dist[edgeList.get(j).dest]) {
					dist[edgeList.get(j).dest] = dist[edgeList.get(j).origin] + edgeList.get(j).weight;
					flag = true;
				}
			}
		}
		
		if(flag) {
			System.out.println("negative cycle existed");
		}else {
			for(int i=1;i<=nV;i++) {
				System.out.print(" " + dist[i]);
			}
		}
	}
	
	public static class Edge implements Comparable<Edge>{
		
		int origin;
		int dest;
		int weight;
		
		public Edge(int origin, int dest, int weight) {
			this.origin = origin;
			this.dest = dest;
			this.weight = weight;
		}
		
		@Override
		public int compareTo(Edge o) {
			if(this.weight > o.weight) {
				return 1;
			}else if(this.weight<o.weight) {
				return -1;
			}else {
				return 0;
			}
		}
	}
}
