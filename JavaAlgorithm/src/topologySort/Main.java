package topologySort;
import java.util.*;

public class Main {

	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		List<ArrayList<Integer>> array; // ������ ����Ǵ� list
		Queue<Integer> queue = new LinkedList<Integer>(); // ���� ���� ������ �ʿ��� ť
		Queue<Integer> result = new LinkedList<Integer>(); // ����� ����Ǵ� ť
		int inDegree[];
		
		int nV,nE,origin,dest; // ����, ������ ��, ������ ����, ����
		
		nV = scan.nextInt();
		nE = scan.nextInt();
		
		array = new ArrayList<ArrayList<Integer>>(nV+1);
		inDegree = new int[nV+1];
		
		// ArrayList �ʱ�ȭ
		for(int i=0;i<=nV;i++) {
			array.add(new ArrayList<Integer>());
		}
		
		// ���� �߰�
		for(int i=0;i<nE;i++) {
			origin = scan.nextInt();
			dest = scan.nextInt();
			array.get(origin).add(dest);
			inDegree[dest]++;
		}
		
		// ��������
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
