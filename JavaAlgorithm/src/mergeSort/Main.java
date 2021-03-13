package mergeSort;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Main {
	
	/*
	// 1. 배열을 활용한 합병 정렬
	public static void mergeSort(int[] arr, int l, int r) {
		
		// basecase
		if(l>=r) {
			return;
		}
		
		int m = (l+r)/2;
		
		mergeSort(arr, l, m);
		mergeSort(arr,m+1,r);
		merge(arr,l,r);
		
	}
	
	public static void merge(int[] arr, int l, int r) {
		
		int[] temp = new int[r-l+1];
		int i = l, m = (l+r)/2, k=0;
		int j = m+1;
		
		while(i<=m && j<=r) {
			
			if(arr[i]<=arr[j]) {
				temp[k++] = arr[i++];
			}else {
				temp[k++] = arr[j++];
			}
		}
		
		while(i<=m) {
			temp[k++] = arr[i++];
		}
		
		while(j<=r) {
			temp[k++] = arr[j++];
		}
		
		for(int z=l;z<r+1;z++) {
			arr[z] = temp[z-l]; 
		}
		
	}
	
	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		
		int[] arr = new int[]{8,5,4,3,2,7,6,1};
		
		for(int i=0;i<arr.length;i++) {
			System.out.print(arr[i]+" ");
		}
		System.out.println();
		
		mergeSort(arr, 0, arr.length-1);
		
		for(int i=0;i<arr.length;i++) {
			System.out.print(arr[i]+" ");
		}
		
	}
	
	*/
	
	// 2. 연결리스트를 이용한 합병정렬
	public static List<Integer> targetList 
		= new LinkedList<Integer>(Arrays.asList(5,7,8,1,2,3,6,4));
	
	public static List<Integer> mergeSort(List<Integer> list) {
		
		if(list.size()<2) {
			return list;
		}
		
		int m= list.size()/2;
		
		List<Integer> list1 = list.subList(0, m);
		List<Integer> list2 = list.subList(m, list.size());
		
		return merge(mergeSort(list1),mergeSort(list2));

	}
	
	public static List<Integer> merge(List<Integer> list1, List<Integer> list2) {
		
		List<Integer> list = new LinkedList<Integer>();
		
		int i = 0, j=0;
		
		while(i<list1.size() && j<list2.size()) {
			if(list1.get(i)<=list2.get(j)) {
				list.add(list1.get(i++));
			}else {
				list.add(list2.get(j++));
			}
		}
		
		while(i<list1.size()) {
			list.add(list1.get(i++));
		}
		
		while(j<list2.size()) {
			list.add(list2.get(j++));
		}
		
		return list;
		
	}
	
	public static void main(String[] args) {
		
		List<Integer> result = new LinkedList<Integer>();
		
		for(int i=0;i<targetList.size();i++) {
			System.out.println(targetList.get(i));
		}
		
		result = mergeSort(targetList);
		
		System.out.println();

		for(int i=0;i<result.size();i++) {
			System.out.println(result.get(i));
		}
	}
}
