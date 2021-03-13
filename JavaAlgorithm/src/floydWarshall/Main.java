package floydWarshall;
import java.util.*;

public class Main {

	public static final int INF=9999999;
	
	public static void main(String[] args) {
		
		int nV, nE;
		int origin, dest, weight;
		int D[][], nxt[][];
		
		Scanner scan = new Scanner(System.in);
		
		nV = scan.nextInt();
		nE = scan.nextInt();
		
		D = new int[nV+1][nV+1]; // 최단거리 테이블
		nxt = new int[nV+1][nV+1]; // s->t를 최소비용으로 가기 위한 s의 다음 경로 테이블
		
		// init D array
		for(int i=1;i<=nV;i++) {
			for(int j=1;j<=nV;j++) {
				if(i==j) {
					continue;
				}
				D[i][j] = INF;
			}
		}
		
		// add edge & init nxt
		// 간선을 추가하고 nxt 배열을 초기화
		for(int i=0;i<nE;i++) {
			origin = scan.nextInt();
			dest = scan.nextInt();
			weight = scan.nextInt();
			
			D[origin][dest] = D[dest][origin] = weight;
			
			nxt[origin][dest] = dest;
			nxt[dest][origin] = origin;
		}
		
		// floyd warshall
		for(int k=1;k<=nV;k++) {
			for(int i=1;i<=nV;i++) {
				for(int j=1;j<=nV;j++) {
					if(i==j) {
						continue;
					}
					if(D[i][j]>D[i][k] + D[k][j]) {
						D[i][j] = D[i][k] + D[k][j];
						nxt[i][j] = nxt[i][k];
					}
				}
			}
		}
		
		// print table D
		for(int i=1;i<=nV;i++) {
			for(int j=1;j<=nV;j++) {
				System.out.print(" " + D[i][j]);
			}
			System.out.println();
		}
		
		System.out.println();
		
		// print table nxt
		for(int i=1;i<=nV;i++) {
			for(int j=1;j<=nV;j++) {
				System.out.print(" " + nxt[i][j]);
			}
			System.out.println();
		}
		
		System.out.println();
		
		// 경로 추적
		for(int i=1;i<=nV;i++) {
			for(int j=1;j<=nV;j++) {
				int tmp = i;
				System.out.print(i + " 에서 " + j + "의 최단경로 : " + i);
				if(i==j) {
					System.out.println();
					continue;
				}
				while(nxt[tmp][j]!=j) {
					tmp = nxt[tmp][j];
					System.out.print(" -> " + tmp);
				}
				System.out.println(" -> " + j);
			}
		}
		
	}

}
