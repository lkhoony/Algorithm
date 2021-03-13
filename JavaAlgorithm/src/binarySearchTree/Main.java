package binarySearchTree;

import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	
	// # 반복문을 사용
	public static TreeNode treeSearch(int k,Tree tree) {
		
		TreeNode node = tree.root;
		
		while(node!=null) {
			
			if(node.key==k) {
				
				return node;
			}
			
			else if(node.key>k) {
				node = node.left;
			}else if(node.key<k) {
				node = node.right;
			}
		}
		
		return node;
		
	}
	
	
	
	public static int findElement(int k, Tree tree) {
		
		TreeNode node = treeSearch(k, tree);
		int key; 
		
		if(node!=null) {
			key = node.key;
		}
		else {
			key = -1;
		}
		
		return key;
		
	}
	
	public static void insertItem(int k, Tree tree) {
		
		TreeNode node = tree.root;
		
		// 1. root가 null일 경우에 대해서 처리가 필요
		if(node==null) {
			tree.root = new TreeNode(k);
			return;
		}
		
		// 2. 그렇지 않은 경우는 트리에 노드가 하나 이상 저장되어있음
		
		// parent 변수를 선언하여 부모노드를 추적
		// root의 parent는 없으므로 null로 초기화
		TreeNode parent = null;
		
		// 잎새노드(null)가 나올 때 까지 탐색
		// 잎새노드에 도달하게 되면 왼쪽자식, 오른쪽자식을 판단하여 노드를 삽입
		while(true) {
			
			parent = node;
			
			if(node.key==k) {
				System.out.println(k + " is already existed");
				break;
			}
			
			if(node.key>k) {
				node = node.left;
				if(node==null) {
					parent.left = new TreeNode(k);
					break;
				}
			}else {
				node = node.right;
				if(node==null) {
					parent.right = new TreeNode(k);
					break;
				}
			}
		}
	}
	
	public static int removeElement(Tree tree, int k) {
		
		TreeNode node = tree.root; // 삭제 될 노드
		TreeNode parent = null; // node의 부모노드
		TreeNode zParent = null; // z의 부모노드
		TreeNode z=null;
		// z : 삭제될 노드 자리에 들어갈 노드
		int result;
		
		// 1. 해당 키에 대한 노드를 탐색
		while(node!=null) {
			
			if(node.key==k) {
				break;
			}
			
			parent = node;
			
			if(node.key>k) {
				node = node.left;
			}else {
				node = node.right;
			}
		}
		
		// 2. 삭제 실행
		// 2.1. 만약 노드가 없다면 -1을 반환
		if(node==null) {
			return -1;
		}
		
		// 2.2. 그렇지 않은 경우 (해당 키를 갖고 있는 노드를 찾았을 때)
		// 2.2.1. 자식 노드중에 하나 이상이 null일 경우
		if(node.left==null || node.right==null) {
			
			z = node.left;
			
			if(node.right!=null) {
				z = node.right;
			}
		}
		
		// 2.2.2. 자식 노드가 둘다 null이 아닐 경우(내부 노드일 경우)
		// 삭제된 노드의 중위순회 계승자로 대체되어야 함
		if(node.left!=null && node.right!=null) {
			
			zParent = node;
			z = node.right;
			
			// z가 왼쪽 자식이 없을 때 까지 parent와 함께 추적
			while(z.left!=null) {
				zParent = z;
				z = z.left;
			}
			
			if(zParent.right==z) {
				zParent.right = z.right;
				z.left = node.left;
			}else if(zParent.left==z) {
				zParent.left = z.right;
				z.left = node.left;
				z.right = node.right;
			}
		}
		
		// parent 노드와 z를 연결해 주는 작업
		if(parent!=null) {
			if(parent.right==node) {
				parent.right = z;
			}else if(parent.left==node){
				parent.left = z;
			}
		}else {
			tree.root = z;
		}
		
		return node.key;
	}
	
	public static void preOrder(TreeNode node) {
		
		if(node==null) {
			return;
		}
		
		System.out.print(" "+node.key);
		preOrder(node.left);
		preOrder(node.right);
		
	}
	
	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		String[] line;
		char operate;
		int result;
		
		Tree tree = new Tree();
		
		while(true) {
			
			line = scan.nextLine().split(" ");
			
			operate = line[0].charAt(0);
			
			if(operate=='i') {
				insertItem(Integer.parseInt(line[1]), tree);
			}else if(operate=='d') {
				result = removeElement(tree, Integer.parseInt(line[1]));
				if(result==-1) {
					System.out.println("X");
				}else {
					System.out.println(result);
				}
			}else if(operate=='s') {
				result = findElement(Integer.parseInt(line[1]),tree);
				if(result==-1) {
					System.out.println("X");
				}else {
					System.out.println(result);
				}
			}else if(operate=='p') {
				preOrder(tree.root);
				System.out.println();
			}else if(operate=='q') {
				break;
			}
		}		
	}

}
