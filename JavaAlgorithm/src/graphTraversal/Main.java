package graphTraversal;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		
		int n,m,s,origin,dest;
		
		Scanner scanner = new Scanner(System.in);
		
		n = scanner.nextInt();
		m = scanner.nextInt();
		s = scanner.nextInt();
		
		Graph graph = new AdjacencyListGraph(n);
		
		for(int i=0;i<m;i++) {
			origin = scanner.nextInt();
			dest = scanner.nextInt();
			graph.addEdge(origin,dest);
		}
		
		graph.traverseGraph(s);
	}

}

