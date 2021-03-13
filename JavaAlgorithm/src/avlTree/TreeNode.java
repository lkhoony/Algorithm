package avlTree;

public class TreeNode<T> {
	
	private T element;
	private TreeNode<T> left;
	private TreeNode<T> right;
	private int height;
	private TreeNode<T> parent;
	
	public TreeNode(T element, TreeNode<T> left, TreeNode<T> right, TreeNode<T> parent, int height){
		this.element = element;
		this.left = left;
		this.right = right;
		this.parent = parent;
		this.height = height;
	}
	
	public T getElement() {
		return element;
	}
	public void setElement(T element) {
		this.element = element;
	}
	public TreeNode<T> getLeft() {
		return left;
	}
	public void setLeft(TreeNode<T> left) {
		this.left = left;
	}
	public TreeNode<T> getRight() {
		return right;
	}
	public void setRight(TreeNode<T> right) {
		this.right = right;
	}
	public int getHeight() {
		return height;
	}
	public void setHeight(int height) {
		this.height = height;
	}
	public TreeNode<T> getParent() {
		return parent;
	}
	public void setParent(TreeNode<T> parent) {
		this.parent = parent;
	}
	
}
