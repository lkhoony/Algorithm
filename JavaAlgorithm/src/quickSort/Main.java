package quickSort;

public class Main {
	
	public static int[] arr;
	
	public static int getPivotIndex(int[] arr, int r, int l) {
		
		int a = arr[l];
		int b = arr[(r+l)/2];
		int c = arr[r];
		
		if(a>=b) {
			
			if(b>=c) {
				return (r+l)/2;
			}else {
				if(a>=c) {
					return r;
				}else
					return l;
			}
			
		}else{
			
			if(a>=c) {
				return l;
			}else {
				if(c>=b) {
					return (r+l)/2;
				}else {
					return r;
				}
			}
		}
	}
	
	public static void swap(int[] arr, int a, int b) {
	
		int tmp = arr[a];
		arr[a] = arr[b];
		arr[b] = tmp;
		
	}
	
	public static void quickSort(int[] arr,int l, int r) {
		
		if(l>=r) {
			return;
		}
		
		int k = getPivotIndex(arr, l, r); // k : pivot index
		int i = l, j = r-1;
		
		swap(arr,r,k);
		
		while(i<=j) {
			
			while(i<=j && arr[i]<=arr[r]) {
				i++;
			}
			
			while(i<=j && arr[j]>=arr[r]) {
				j--;
			}
			
			if(i<j) {
				swap(arr,i,j);
			}
		}
		
		swap(arr,i,r);
		
		quickSort(arr, l, i-1);
		quickSort(arr,i+1,r);

	}
	
	public static void main(String[] args) {
		
		arr = new int[] {5,4,3,1,2,6,8,7};
		
		for(int i=0;i<arr.length;i++) {
			System.out.print(arr[i]+" ");
		}
		
		quickSort(arr, 0, arr.length-1);
		
		System.out.println();
		for(int i=0;i<arr.length;i++) {
			System.out.print(arr[i]+" ");
		}
		
	}

}
