package graphTraversal;

import java.util.LinkedList;
import java.util.Queue;

public class AdjacencyMatrixGraph implements Graph{
	
	private int adjMatrix[][];
	private boolean visitArr[];
	
	public AdjacencyMatrixGraph(int vNum) {
		
		this.adjMatrix = new int[vNum+1][vNum+1];
		this.visitArr = new boolean[vNum+1];
	}
	
	@Override
	public void addEdge(int origin, int dest) {
		
		this.adjMatrix[origin][dest] = 1;
		if(origin!=dest) {
			this.adjMatrix[dest][origin] = 1;
		}
		
	}
	
	@Override
	public void dfs(int index) {
		
		this.visitArr[index]=true;
		System.out.println(index);
		
		for(int i=0;i<this.adjMatrix[index].length;i++) {
			
			if(this.adjMatrix[index][i]!=0) {
				dfs(i);
			}
		}
	}
	
	@Override
	public void bfs(int index) {
		
		int first;
		Queue<Integer> queue = new LinkedList<Integer>();
		
		queue.add(index);
		visitArr[index] = true;
		
		while(!queue.isEmpty()) {
			
			first = queue.poll();
			System.out.println(first);
			
			for(int i=0;i<this.adjMatrix[first].length;i++) {
				
				if(adjMatrix[first][i]!=0) {
					if(!this.visitArr[i]) {
						queue.add(i);
						this.visitArr[i] = true;
					}
				}
			}
		}
	}
	
	@Override
	public void traverseGraph(int startVertex) {
		dfs(startVertex);
	}
	
	@Override
	public void clearVisitArr() {
		
		for(int i=0;i<this.visitArr.length;i++) {
			this.visitArr[i]=false;
		}
	}
	
}
