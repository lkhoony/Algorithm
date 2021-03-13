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
		
		D = new int[nV+1][nV+1]; // �ִܰŸ� ���̺�
		nxt = new int[nV+1][nV+1]; // s->t�� �ּҺ������ ���� ���� s�� ���� ��� ���̺�
		
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
		// ������ �߰��ϰ� nxt �迭�� �ʱ�ȭ
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
		
		// ��� ����
		for(int i=1;i<=nV;i++) {
			for(int j=1;j<=nV;j++) {
				int tmp = i;
				System.out.print(i + " ���� " + j + "�� �ִܰ�� : " + i);
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
