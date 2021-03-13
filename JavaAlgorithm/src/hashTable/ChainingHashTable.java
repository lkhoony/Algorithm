package hashTable;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class ChainingHashTable implements HashTable{

	private LinkedList<Integer> hashTable[];
	private int M;
	
	public ChainingHashTable(int M) {
		
		this.M = M;
		this.hashTable = new LinkedList[M];
		
		for(int i=0;i<M;i++) {
			this.hashTable[i] = new LinkedList<Integer>();
		}
	}
	
	@Override
	public int deleteKey(int key) {
		
		for(int i=0;i<this.M;i++) {
			int listSize = this.hashTable[i].size();
			for(int j=0;j<listSize;j++) {
				if(this.hashTable[i].get(j)==key) {
					this.hashTable[i].remove(j);
					return j+1;
				}
			}
		}
		return 0;
	}
	
	@Override
	public void insertKey(int key) {
		int index = this.hashFunction(key);
		this.hashTable[index].addFirst(key);
	}
	
	@Override
	public void printTable() {
		
		for(int i=0;i<this.M;i++) {
			
			int listSize = this.hashTable[i].size();
			for(int j=0;j<listSize;j++) {
				System.out.print(" "+this.hashTable[i].get(j));
			}
		}
	}
	
	@Override
	public int searchKey(int key) {
		
		for(int i=0;i<this.M;i++) {
			
			int listSize = this.hashTable[i].size();
			for(int j=0;j<listSize;j++) {
				if(this.hashTable[i].get(j)==key) {
					return j+1;
				}
			}
		}
		
		return 0;
		
	}
	
	@Override
	public int hashFunction(int key) {

		return key % this.M;
	}
}
