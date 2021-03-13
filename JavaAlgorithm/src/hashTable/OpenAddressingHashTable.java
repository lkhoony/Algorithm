package hashTable;

public class OpenAddressingHashTable implements HashTable{
	
	private int nMax;
	private int n; 
	private int M;
	private int q;
	private int hashTable[];
	
	public OpenAddressingHashTable(int nMax, int M, int q) {
		
		this.nMax = nMax;
		this.n = 0;
		this.M = M;
		this.q = q;
		this.hashTable = new int[M];
	}
	
	@Override
	public int deleteKey(int key) {
		
		int i=0;
		int index = (this.hashFunction(key)+this.reHashFunction(key)*i)%M;
		
		while(this.hashTable[index]!=0) {
			
			if(this.hashTable[index]==key) {
				this.hashTable[index]=0;
				return index;
			}
		}
		
		return -1;
	}
	
	@Override
	public void insertKey(int key) {
		
		if(this.n>=nMax) {
			System.out.println("hash table is already full");
			return;
		}
		
		int i = 0;
		int index = (this.hashFunction(key)+this.reHashFunction(key)*i)%M;
		
		while(this.hashTable[index]!=0) {
			System.out.print('C');
			i++;
			index = (this.hashFunction(key)+this.reHashFunction(key)*i)%M;
		}
		System.out.println(index);
		this.n =this.n +1;
		this.hashTable[index] = key;
	}
	
	@Override
	public void printTable() {
		
		for(int i=0;i<this.M;i++) {
			System.out.print(" " + this.hashTable[i]);
		}
		
		System.out.println();
	}
	
	@Override
	public int searchKey(int key) {
		
		int i=0;
		int index = (this.hashFunction(key)+this.reHashFunction(key)*i)%M;
		
		while(this.hashTable[index]!=0) {
			
			if(this.hashTable[index]==key) {
				return index;
			}
		}
		
		return -1;
	}
	
	@Override
	public int hashFunction(int key) {
		// TODO Auto-generated method stub
		return key%M;
	}
	
	public int reHashFunction(int key) {
		return this.q-(key%this.q);
	}
}
