package hashTable;

public interface HashTable {
	
	public void insertKey(int key);
	public int searchKey(int key);
	public int deleteKey(int key);
	public void printTable();
	public int hashFunction(int key);
}
