package graph;

public class AdjacencyMatrixGraph implements Graph{
	
	private int[][] adjacencyMatrix;
	
	public AdjacencyMatrixGraph(int vertexNum) {
		
		this.adjacencyMatrix = new int[vertexNum+1][vertexNum+1];
		
	}
	

	@Override
	public void insertVertex(int index) {
		// 클래스를 생성 할 때 모든 요소를 0으로 초기화 해서 vertex 입력 불필요
	}
	
	@Override
	public void insertEdge(int origin, int dest) {
		this.adjacencyMatrix[origin][dest] = 1;
		this.adjacencyMatrix[dest][origin] = 1;
	}
	
	@Override
	public void adjacentVertices(int index) {
		
		System.out.print("Vertex " + index + " : ");
		
		for(int i=0;i<this.adjacencyMatrix[index].length;i++) {
			
			if(this.adjacencyMatrix[index][i]!=0) {
				System.out.print(this.adjacencyMatrix[index][i]+" ");
			}			
		}

	}
	
}
