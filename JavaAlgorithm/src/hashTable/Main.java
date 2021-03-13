package hashTable;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		String[] line;
		char operate;
		int key,result;
		
		HashTable hashTable = new ChainingHashTable(scan.nextInt());
		
		scan.nextLine();
		
		while(true) {

			line = scan.nextLine().split(" ");
			operate = line[0].charAt(0);
			
			if(operate=='i') {
				hashTable.insertKey(Integer.parseInt(line[1]));
			}else if(operate=='s') {
				result = hashTable.searchKey(Integer.parseInt(line[1]));
				if(result!=-1) {
					System.out.println(result);
				}else{
					System.out.println("0");
				}
			}else if(operate=='d') {
				result = hashTable.deleteKey(Integer.parseInt(line[1]));
				if(result!=-1) {
					System.out.println(result);
				}else{
					System.out.println("0");
				}
			}else if(operate=='p') {
				hashTable.printTable();
			}else if(operate=='e') {
				break;
			}
		}
	}

}
