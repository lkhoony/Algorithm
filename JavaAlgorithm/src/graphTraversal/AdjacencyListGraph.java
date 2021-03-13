package graphTraversal;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class AdjacencyListGraph implements Graph{
	
	private ArrayList<ArrayList<Integer>> adjList;
	private boolean[] visitArr;
	
	// 생성자에서 각각의 인접 리스트를 초기화
	public AdjacencyListGraph(int vNum) {
		
		this.adjList = new ArrayList<ArrayList<Integer>>(vNum+1);
		
		for(int i=0;i<=vNum;i++) {
			this.adjList.add(new ArrayList<Integer>());
		}
		
		visitArr = new boolean[vNum+1];
	}
	
	
	@Override
	public void addEdge(int origin, int dest) {
		this.adjList.get(origin).add(dest);
		
		if(origin!=dest) {
			this.adjList.get(dest).add(origin);
		}
	}
	
	@Override
	public void dfs(int index) {
		
		this.visitArr[index] = true;
		System.out.println(index);

		for(int i : this.adjList.get(index)) {
			
			if(!this.visitArr[i]) {
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
			
			for(int i=0;i<this.adjList.get(first).size();i++) {
				
				if(!this.visitArr[this.adjList.get(first).get(i)]) {
					queue.add(this.adjList.get(first).get(i));
					this.visitArr[this.adjList.get(first).get(i)] = true;
				}
			}
		}
		
	}
	
	@Override
	public void traverseGraph(int startVertex) {
		
		bfs(startVertex);
		clearVisitArr();
		
	}
	
	@Override
	public void clearVisitArr() {
		
		for(int i=0;i<this.visitArr.length;i++) {
			this.visitArr[i] = false;
		}
	}
	
}
