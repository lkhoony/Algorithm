package graphTraversal;

public interface Graph{
	
	public void addEdge(int origin, int dest);
	public void dfs(int index);
	public void bfs(int index);
	public void traverseGraph(int startVertex);
	public void clearVisitArr();
}
