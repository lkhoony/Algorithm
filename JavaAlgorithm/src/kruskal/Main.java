package kruskal;
import java.util.*;

public class Main {
	
	public static int[] parent;
	
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
			if(this.weight < o.weight) {
				return -1;
			}else if(this.weight > o.weight) {
				return 1;
			}else {
				return 0;
			}
		};
		
	}
	
	public static void initSet(int nV) {
		parent = new int[nV+1];
		for(int i=0;i<=nV;i++) {
			parent[i] = i;
		}
	}
	public static int find(int x) {
		
		if(parent[x] == x) {
			return x;
		}
		
		return parent[x] = find(parent[x]);
		
	}
	
	public static void union(int x, int y) {
		
		int n = find(x);
		int m = find(y);
		
		if(n!=m) {
			parent[m] = n;
		}
	}
	
	public static void main(String[] args) {
		
		int nV, nE, origin, dest, weight, weightSum = 0;
		ArrayList<Edge> result;
		PriorityQueue<Edge> pq;
		
		Scanner scan = new Scanner(System.in);
		
		nV = scan.nextInt();
		nE = scan.nextInt();
		
		result = new ArrayList<Edge>(nE);
		pq = new PriorityQueue<Edge>(nE);
		
		initSet(nV);
		
		for(int i=0;i<nE;i++) {
			origin = scan.nextInt();
			dest = scan.nextInt();
			weight = scan.nextInt();
			pq.add(new Edge(origin, dest, weight));
		}
		
		Edge edge;
		
		while(!pq.isEmpty()) {
			
			edge = pq.poll();
			
			if(find(edge.origin)!=find(edge.dest)) {
				weightSum += edge.weight;
				result.add(edge);
				union(edge.origin, edge.dest);
				
			}
		}
		
		for(int i=0;i<result.size();i++) {
			System.out.println(result.get(i).origin + " -> " + result.get(i).dest);
		}
		
		System.out.println("weight sum : " + weightSum);
		
	}

}
/*
6 9
1 2 2
1 3 6
1 5 7
2 3 5
2 4 7
3 4 9
3 5 8
4 6 4
5 6 3
 */
