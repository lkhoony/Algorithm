package avlTree;

public interface Tree<T> {

	public void insertItem(T element);
	public void preOrderTraverse(TreeNode<T> node);
	public void inOrderTraverse(TreeNode<T> node);
	public void postOrderTraverse(TreeNode<T> node);
	public TreeNode<T> getRoot();
	public void setRoot(TreeNode<T> node);
	public TreeNode<T> removeElement(T element);
	public TreeNode<T> searchTree(T element);
	public void restruct(TreeNode<T> node);
	public void updateHeight(TreeNode<T> node);
	public int getHeightDiff(TreeNode<T> node);
	public TreeNode<T> rotate(TreeNode<T> node);
	
}
