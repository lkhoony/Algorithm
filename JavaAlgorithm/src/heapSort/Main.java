package heapSort;

import java.util.Scanner;

public class Main {
	
	private static int heap[] = new int[100];
	private static int heapNum = 0;
	
	public static void swap(int arr[], int a, int b) {
		
		int tmp = arr[a];
		arr[a] = arr[b];
		arr[b] = tmp;
		
	}
	
	public static void insertHeap(int e) {
		
		heap[++heapNum] = e;
		upHeap(heapNum);
	}
	
	public static void upHeap(int index) {
		
		if(index<=1) {
			return;
		}
		
		if(heap[index/2]<heap[index]) {
			swap(heap,index/2,index);
			upHeap(index/2);
		}
		
	}
	
	public static void downHeap(int index) {
		
		if(index*2>heapNum) {
			return;
		}
		
		int biggerIndex = index * 2;
		
		if(index*2+1<=heapNum) {
			if(heap[biggerIndex]<heap[index*2+1]) {
				biggerIndex = index*2+1;
			}
		}
		
		if(heap[index]<heap[biggerIndex]) {
			swap(heap,index,biggerIndex);
		}
		
		downHeap(biggerIndex);
	}
	
	public static int removeFirst() {
		
		int first = heap[1];
		
		heap[1] = heap[heapNum--];
		downHeap(1);
		return first;
		
	}
	
	public static void rBuildHeap(int index) {
		
		if(index>heapNum) {
			return;
		}
		
		rBuildHeap(index*2);
		rBuildHeap(index*2+1);
		downHeap(index);
		
	}
	
	public static void heapSort() {
		
		int hN = heapNum;
		
		while(heapNum!=0) {
			
			swap(heap,1,heapNum);
			
			heapNum--;
			
			downHeap(1);
			
		}
		
		heapNum = hN;
	}
	
	public static void printHeap() {
		
		for(int i=0;i<heapNum;i++) {
			System.out.print(heap[i+1] + " ");
		}
	}
	
	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		
		for(int i=0;i<8;i++) {
			insertHeap(scan.nextInt());
		}
		
		printHeap();
		
		heapSort();
		
		System.out.println();
		
		printHeap();
	}

}
