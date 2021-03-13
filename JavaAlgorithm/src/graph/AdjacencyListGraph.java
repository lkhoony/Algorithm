package graph;

import java.util.ArrayList;

public class AdjacencyListGraph implements Graph{
	
	private ArrayList<ArrayList<Integer>> adjacencyList;
	
	public AdjacencyListGraph(int vertexNum) {
		this.adjacencyList = new ArrayList<ArrayList<Integer>>(vertexNum+1);
	}
	
	@Override
	public void insertVertex(int index) {
		this.adjacencyList.add(new ArrayList<Integer>());
	}
	
	@Override
	public void insertEdge(int origin, int dest) {
		this.adjacencyList.get(origin).add(dest);
		this.adjacencyList.get(dest).add(origin);
	}
	
	@Override
	public void adjacentVertices(int index) {
		
		int arrLen = this.adjacencyList.get(index).size();
		
		System.out.print("Vertex " + index + " : ");
		
		for(int i=0;i<arrLen;i++) {
			
			System.out.print(this.adjacencyList.get(index).get(i)+" ");
		}
		
		System.out.println();
	}
	
}
 