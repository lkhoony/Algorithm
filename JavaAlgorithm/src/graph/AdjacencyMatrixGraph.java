package graph;

public class AdjacencyMatrixGraph implements Graph{
	
	private int[][] adjacencyMatrix;
	
	public AdjacencyMatrixGraph(int vertexNum) {
		
		this.adjacencyMatrix = new int[vertexNum+1][vertexNum+1];
		
	}
	

	@Override
	public void insertVertex(int index) {
		// Ŭ������ ���� �� �� ��� ��Ҹ� 0���� �ʱ�ȭ �ؼ� vertex �Է� ���ʿ�
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
