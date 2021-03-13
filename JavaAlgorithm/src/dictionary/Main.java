package dictionary;

public class Main {
	
	public static int[] dictionary;
	
	public static int findElement(int k, int l, int r) {
		
		if(l>r) {
			return -1;
		}
		
		int m = (l+r)/2;
		
		if(dictionary[m]==k) {
			return m;
			
		}else {
			if(dictionary[m]>k) {
				return findElement(k,l,m-1);
			}else {
				return findElement(k,m+1,r);
			}
		}
		
	}
	
	public static void main(String[] args) {
		
		dictionary = new int[] {1,2,3,4,5,6,7,8};
		
		System.out.println(findElement(5, 0, dictionary.length-1));
	}

}
