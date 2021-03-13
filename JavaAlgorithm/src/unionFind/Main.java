package unionFind;
import java.util.*;

public class Main {
	
	public static int[] set;
	
	public static void initSet(int N){
		set = new int[N+1];
		for(int i=0;i<=N;i++) {
			set[i] = i;
		}
	}
	
	public static void union(int x, int y) {
		
		int n = find(x);
		int m = find(y);
		
		set[m] = n;
	}
	
	public static int find(int n) {
		
		if(set[n]==n) {
			return n;
		}
		
		return set[n] = find(set[n]);
	}
	
	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		
		initSet(scan.nextInt());
		
		union(1,2);
		union(2,3);
		
		for(int i=1;i<set.length;i++) {
			System.out.print(" "  + set[i]);
		}
	}

}
