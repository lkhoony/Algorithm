package primJarnik;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

public class Main {
	
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
			
			if(this.weight>o.weight) {
				return 1;
			}else if(this.weight<o.weight) {
				return -1;
			}else {
				return 0;
			}
		}
	}
	
	public static void main(String[] args) {
		
		int nV, nE,origin,dest,weight;
		boolean visit[];
		ArrayList<ArrayList<Edge>> vertexList;
		PriorityQueue<Edge> pq;
		Scanner scan = new Scanner(System.in);
		Queue<Edge> result = new LinkedList<Edge>();
		nV = scan.nextInt();
		nE = scan.nextInt();
		
		vertexList = new ArrayList<ArrayList<Edge>>(nV+1);
		
		for(int i=0;i<=nV;i++) {
			vertexList.add(new ArrayList<Edge>());
		}
		
		for(int i=0;i<nE;i++) {
			origin = scan.nextInt();
			dest = scan.nextInt();
			weight = scan.nextInt();
			vertexList.get(origin).add(new Edge(origin,dest,weight));
			vertexList.get(dest).add(new Edge(dest,origin,weight));
		}
		
		// 1번째 노드를 루트로 하는 MST
		pq = new PriorityQueue<Edge>();
		visit = new boolean[nV+1];
		Edge edge;
		int sumWeight = 0;
		
		for(int i=0;i<vertexList.get(1).size();i++) {
			pq.add(vertexList.get(1).get(i));
		}
		
		visit[1] = true;
		
		while(!pq.isEmpty()) {
			
			edge = pq.poll();
			if(visit[edge.dest]) {
				continue;
			}
			
			visit[edge.dest] = true;
			result.add(edge);
			sumWeight += edge.weight;
			
			for(int i=0;i<vertexList.get(edge.dest).size();i++) {
				if(visit[vertexList.get(edge.dest).get(i).dest]) {
					continue;
				}
				pq.add(vertexList.get(edge.dest).get(i));
			}
		}
		
		System.out.println("MST : ");
		while(!result.isEmpty()) {
			edge = result.poll();
			System.out.println(edge.origin + " -> " + edge.dest);
		}
		
		System.out.println("Sum of Weight : " + sumWeight);
		
	}

}

/*
6 9
1 2 2 
1 3 6
1 6 7
2 3 5
2 4 7
3 4 9
3 6 8
4 5 4
5 6 3 
 */
