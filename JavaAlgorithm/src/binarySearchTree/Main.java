package binarySearchTree;

import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	
	// # �ݺ����� ���
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
		
		// 1. root�� null�� ��쿡 ���ؼ� ó���� �ʿ�
		if(node==null) {
			tree.root = new TreeNode(k);
			return;
		}
		
		// 2. �׷��� ���� ���� Ʈ���� ��尡 �ϳ� �̻� ����Ǿ�����
		
		// parent ������ �����Ͽ� �θ��带 ����
		// root�� parent�� �����Ƿ� null�� �ʱ�ȭ
		TreeNode parent = null;
		
		// �ٻ����(null)�� ���� �� ���� Ž��
		// �ٻ���忡 �����ϰ� �Ǹ� �����ڽ�, �������ڽ��� �Ǵ��Ͽ� ��带 ����
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
		
		TreeNode node = tree.root; // ���� �� ���
		TreeNode parent = null; // node�� �θ���
		TreeNode zParent = null; // z�� �θ���
		TreeNode z=null;
		// z : ������ ��� �ڸ��� �� ���
		int result;
		
		// 1. �ش� Ű�� ���� ��带 Ž��
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
		
		// 2. ���� ����
		// 2.1. ���� ��尡 ���ٸ� -1�� ��ȯ
		if(node==null) {
			return -1;
		}
		
		// 2.2. �׷��� ���� ��� (�ش� Ű�� ���� �ִ� ��带 ã���� ��)
		// 2.2.1. �ڽ� ����߿� �ϳ� �̻��� null�� ���
		if(node.left==null || node.right==null) {
			
			z = node.left;
			
			if(node.right!=null) {
				z = node.right;
			}
		}
		
		// 2.2.2. �ڽ� ��尡 �Ѵ� null�� �ƴ� ���(���� ����� ���)
		// ������ ����� ������ȸ ����ڷ� ��ü�Ǿ�� ��
		if(node.left!=null && node.right!=null) {
			
			zParent = node;
			z = node.right;
			
			// z�� ���� �ڽ��� ���� �� ���� parent�� �Բ� ����
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
		
		// parent ���� z�� ������ �ִ� �۾�
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
