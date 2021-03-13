package topologySort;
import java.util.*;

public class Main {

	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		List<ArrayList<Integer>> array; // 정점이 저장되는 list
		Queue<Integer> queue = new LinkedList<Integer>(); // 위상 정렬 과정에 필요한 큐
		Queue<Integer> result = new LinkedList<Integer>(); // 결과가 저장되는 큐
		int inDegree[];
		
		int nV,nE,origin,dest; // 정점, 간선의 수, 간선의 시점, 종점
		
		nV = scan.nextInt();
		nE = scan.nextInt();
		
		array = new ArrayList<ArrayList<Integer>>(nV+1);
		inDegree = new int[nV+1];
		
		// ArrayList 초기화
		for(int i=0;i<=nV;i++) {
			array.add(new ArrayList<Integer>());
		}
		
		// 간선 추가
		for(int i=0;i<nE;i++) {
			origin = scan.nextInt();
			dest = scan.nextInt();
			array.get(origin).add(dest);
			inDegree[dest]++;
		}
		
		// 위상정렬
		for(int i=1;i<=nV;i++) {
			if(inDegree[i]==0) {
				queue.offer(i);
			}
		}
		
		while(!queue.isEmpty()) {
			
			int node = queue.poll();
			
			for(int i=0;i<array.get(node).size();i++) {
				if(--inDegree[array.get(node).get(i)]==0) {
					queue.offer(array.get(node).get(i));
				}
			}
			result.offer(node);
		}
		
		if(result.size()!=nV) {
			System.out.println("cycle is existed");
			return;
		}
		
		System.out.println(result);
		
	}

}
