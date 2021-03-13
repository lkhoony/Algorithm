package graph;

public interface Graph {
	
	public void insertVertex(int index);
	public void insertEdge(int origin, int dest);
	public void adjacentVertices(int index);
	
}
