package priorityQueue;

import java.util.Scanner;

public class Main {
	
	public static void selectionSort(int arr[]) {
		
		int minLoc,tmp;
		
		for(int i=0;i<arr.length-1;i++) {
			minLoc=i;
			for(int j=i+1;j<arr.length;j++) {
				if(arr[minLoc]>arr[j]){
					minLoc=j;
				}
			}
			if(i!=minLoc) {
				tmp=arr[i];
				arr[i] = arr[minLoc];
				arr[minLoc] = tmp;
			}
		}
	}
	
	public static void insertionSort(int arr[]) {
		
		int j,save;
		
		for(int i=1;i<arr.length;i++) {
			j=i-1;
			save = arr[i];
			
			while(j>0 && arr[j]>save) {
				arr[j+1] = arr[j];
				j--;
			}
			
			arr[j+1]=save;
		}
	}
	
	public static void main(String args[]) {
		
		int N;
		int arr[];
		
		Scanner scan = new Scanner(System.in);
		
		N = scan.nextInt();
		
		arr = new int[N];
		
		for(int i=0;i<N;i++) {
			arr[i] = scan.nextInt();
		}
		
		// 정렬 전 배열을 출력
		for(int i=0;i<N;i++) {
			System.out.print(arr[i]+" ");
		}
		
		System.out.println();
		
		selectionSort(arr);
		
		// 정렬 후 배열을 출력
		for(int i=0;i<N;i++) {
			System.out.print(arr[i]+" ");
		}
		
	}
}
