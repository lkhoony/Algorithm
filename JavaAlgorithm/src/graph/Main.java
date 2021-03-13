package graph;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) {
		
		Scanner scanner = new Scanner(System.in);
		
		int vertexNum = scanner.nextInt();
		int edgeNum = scanner.nextInt();
		int origin;
		int dest;
		
		Graph graph = new AdjacencyListGraph(vertexNum);
		
		for(int i=0;i<=vertexNum;i++) {
			graph.insertVertex(i);
		}
		
		for(int i=0;i<edgeNum;i++) {
			
			origin = scanner.nextInt();
			dest = scanner.nextInt();
			
			graph.insertEdge(origin , dest);
		}
		
		for(int i=0;i<=vertexNum;i++) {
			graph.adjacentVertices(i);
		}
	}

}
