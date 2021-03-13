package dp;

public class Main {

	public static long d[] = new long[101];
	
	public static long fibo(int n) {
		
		// 상향식 방법
//		if(n==1 || n==2) {
//			return 1;
//		}
//		
//		if(d[n]!=0) {
//			return d[n];
//		}
//		
//		d[n] = fibo(n-1) + fibo(n-2);
//		return d[n];
		
		// 하향식 방법
		d[1] = 1;
		d[2] = 1;
		
		for(int i=3;i<=n;i++) {
			d[i] = d[i-1] + d[i-2];
		}
		
		return d[n];
	}
	
	public static void main(String[] args) {
		System.out.println(fibo(100));
	}

}
