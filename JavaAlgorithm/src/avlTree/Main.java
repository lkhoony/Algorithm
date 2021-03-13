package avlTree;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {

		Tree<Integer> tree = new AVLTree<Integer>();
		TreeNode<Integer> result;
		
		Scanner scan = new Scanner(System.in);
		String line[];
		char operate;
		int element;
		
		while(true) {
			
			line = scan.nextLine().split(" ");
			operate = line[0].charAt(0);
			
			if(operate=='i') {
				tree.insertItem(Integer.parseInt(line[1]));
			}else if(operate=='d') {
				result = tree.removeElement(Integer.parseInt(line[1]));
				if(result==null) {
					System.out.println("X");
				}else {
					System.out.println(result.getElement());
				}
			}else if(operate=='s') {
				result = tree.searchTree(Integer.parseInt(line[1]));
				if(result==null) {
					System.out.println("X");
				}else {
					System.out.println(result.getElement());
				}
			}else if(operate=='p') {
				tree.preOrderTraverse(tree.getRoot());
				System.out.println();
			}else if(operate=='q') {
				break;
			}
		}
	}

}
