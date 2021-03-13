package avlTree;

public class AVLTree<T extends Comparable<T>> implements Tree<T> {
	
	// ��Ʈ ��带 ��������� ����
	private TreeNode<T> root;
	
	public AVLTree() {
		this.root = null;
	}
	
	@Override
	public void insertItem(T element) {
		
		TreeNode<T> node = this.getRoot();
		TreeNode<T> parent = null;
		
		// root�� null�̸� ���ο� ��带 ����� root�� ����
		if(node==null) {
			this.setRoot(new TreeNode<T>(element, null, null, null,0));
			return;
		}
		
		// root�� null�� �ƴ� ���
		while(node!=null) {
			
			parent = node;
			
			if(node.getElement().compareTo(element)==0) {
				System.out.println(element + " is already exist");
				return;
				
			}else if(node.getElement().compareTo(element)>0) {
				node = node.getLeft();
				if(node==null) {
					parent.setLeft(new TreeNode<T>(element, null, null, parent, 0));
					this.restruct(parent.getLeft());
				}
			}else if(node.getElement().compareTo(element)<0) {
				node = node.getRight();
				if(node==null) {
					parent.setRight(new TreeNode<T>(element, null, null, parent, 0));
					this.restruct(parent.getRight());
				}
			}
		}
	}

	@Override
	public void preOrderTraverse(TreeNode<T> node) {
		if(node==null) {
			return;
		}
		
		System.out.print(" "+node.getElement());
		preOrderTraverse(node.getLeft());
		preOrderTraverse(node.getRight());
	}

	@Override
	public void inOrderTraverse(TreeNode<T> node) {
		
		if(node==null) {
			return;
		}
		
		inOrderTraverse(node.getLeft());
		System.out.print(" "+node.getElement());
		inOrderTraverse(node.getRight());
		
	}

	@Override
	public void postOrderTraverse(TreeNode<T> node) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public TreeNode<T> removeElement(T element) {
		
		TreeNode<T> node = this.getRoot();
		TreeNode<T> z=null;
		// element�� ���� node Ž��
		// �ݺ����� �� ���� node�� null
		while(node!=null) {
			
			if(node.getElement().compareTo(element)==0) {
				break;
			}
			
			if(node.getElement().compareTo(element)>0) {
				node = node.getLeft();
			}else {
				node = node.getRight();
			}
		}
		
		if(node==null) {
			return null;
		}
		
		// 1. ����, ������ �ڽ� �� �ϳ��� null
		if(node.getLeft()==null || node.getRight()==null) {
			z = node.getLeft();
			
			if(node.getRight()!=null) {
				z = node.getRight();
			}
		}
		
		// 2. ����, ������ �ڽ� ��� null�� �ƴ� ���
		else if(node.getLeft()!=null && node.getRight()!=null) {
			// node�� ������ȸ �İ��ڸ� ã��
			z= node.getRight();
			
			while(z.getLeft()!=null) {
				z = z.getLeft();
			}
			
			if(node.getRight()==z) {
				 z.setLeft(node.getLeft());
				 if(node.getLeft()!=null) {
					 node.getLeft().setParent(z); 
				 }
			}else {
				
				z.getParent().setLeft(z.getRight());
				
				if(z.getRight()!=null) {
					z.getRight().setParent(z.getParent());
				}
				
				z.setLeft(node.getLeft());
				if(node.getLeft()!=null) {
					node.getLeft().setParent(z);
				}
				
				z.setRight(node.getRight());
				if(node.getRight()!=null) {
					node.getRight().setParent(z);
				}
			}
		}

		if(node.getParent()!=null) {
			if(node.getParent().getLeft()==node) {
				node.getParent().setLeft(z);
				if(z!=null) {
					z.setParent(node.getParent());
				}
			}else {
				node.getParent().setRight(z);
				if(z!=null) {
					z.setParent(node.getParent());
				}
			}
		}else {
			this.setRoot(z);
			if(z!=null) {
				z.setParent(null);
			}
		}
		
		this.restruct(z);
		return node;
	}
	
	@Override
	public void restruct(TreeNode<T> node) {
		
		int heightDiff;
		
		while(node!=null) {
			
			heightDiff = this.getHeightDiff(node);
			// �ұ��� ����
			if(heightDiff<-1 || heightDiff >1) {
				node = this.rotate(node).getParent();
			}else {
				updateHeight(node);
				node = node.getParent();
			}
		}
	}
	
	@Override
	public void updateHeight(TreeNode<T> node) {
		
		int left;
		int right;
		
		if(node.getLeft()==null) {
			left = -1;
		}else {
			left = node.getLeft().getHeight();
		}
		
		if(node.getRight()==null) {
			right = -1;
		}else {
			right = node.getRight().getHeight();
		}
		
		if(left>=right) {
			node.setHeight(left+1);
		}else {
			node.setHeight(right+1);
		}
		
	}
	
	@Override
	public int getHeightDiff(TreeNode<T> node) {
		
		int left,right;
		
		if(node.getLeft()==null) {
			left=-1;
		}else {
			left = node.getLeft().getHeight();
		}
		
		if(node.getRight()==null) {
			right=-1;
		}else {
			right = node.getRight().getHeight();
		}
		return left-right;
	}
	
	@Override
	public TreeNode<T> rotate(TreeNode<T> node) {
		
		TreeNode<T> x,y,z;

		if(this.getHeightDiff(node)>0) {
			//LL
			if(this.getHeightDiff(node.getLeft())>0) {
				
				x = node;
				y = node.getLeft();
				z = y.getLeft();
				
				x.setLeft(y.getRight());
				
				if(y.getRight()!=null) {
					y.getRight().setParent(x);
				}
				
				y.setRight(x);
				
				y.setParent(x.getParent());
				x.setParent(y);
				
				if(y.getParent()==null) {
					this.setRoot(y);
				}else {
					if(y.getParent().getLeft()==x) {
						y.getParent().setLeft(y);
					}else {
						y.getParent().setRight(y);
					}
				}
				this.updateHeight(z);
				this.updateHeight(x);
				this.updateHeight(y);
				
				return y;
			}
			//LR
			else {
				
				x = node;
				y = node.getLeft();
				z = y.getRight();
				
				y.setRight(z.getLeft());
				if(z.getLeft()!=null) {
					z.getLeft().setParent(y);
				}
				
				x.setLeft(z.getRight());
				if(z.getRight()!=null) {
					z.getRight().setParent(x);
				}
				
				z.setLeft(y);
				z.setRight(x);
				z.setParent(x.getParent());
				
				x.setParent(z);
				y.setParent(z);
				
				if(z.getParent()==null) {
					this.setRoot(z);
				}else {
					if(z.getParent().getLeft()==x) {
						z.getParent().setLeft(z);
					}else {
						z.getParent().setRight(z);
					}
				}
				
				this.updateHeight(x);
				this.updateHeight(y);
				this.updateHeight(z);
				
				return z;
			}
			
		}

		else if(this.getHeightDiff(node)<0) {
			
			// RRȸ��
			if(this.getHeightDiff(node.getRight())<0) {
				
				x = node;
				y = node.getRight(); 
				z = y.getRight();
				
				x.setRight(y.getLeft());
				
				if(y.getLeft()!=null) {
					y.getLeft().setParent(x);
				}
				
				y.setLeft(x);
				
				y.setParent(x.getParent());
				x.setParent(y);
				
				if(y.getParent()==null) {
					this.setRoot(y);
				}else {
					if(y.getParent().getLeft()==x) {
						y.getParent().setLeft(y);
					}else {
						y.getParent().setRight(y);
					}
				}
				this.updateHeight(z);
				this.updateHeight(x);
				this.updateHeight(y);
				return y;
			}
			// RLȸ��
			else {
				
				x = node;
				y = node.getRight();
				z = y.getLeft();
				
				y.setLeft(z.getRight());
				if(z.getRight()!=null) {
					z.getRight().setParent(y);
				}
				
				x.setRight(z.getLeft());
				if(z.getLeft()!=null) {
					z.getLeft().setParent(x);
				}
				
				z.setRight(y);
				z.setLeft(x);
				z.setParent(x.getParent());
				
				x.setParent(z);
				y.setParent(z);
				
				if(z.getParent()==null) {
					this.setRoot(z);
				}else {
					if(z.getParent().getLeft()==x) {
						z.getParent().setLeft(z);
					}else {
						z.getParent().setRight(z);
					}
				}
				
				this.updateHeight(x);
				this.updateHeight(y);
				this.updateHeight(z);
				
				return z;
			}
		}
		
		return null;
	}
	
	@Override
	public TreeNode<T> searchTree(T element) {
		
		TreeNode<T> node = this.getRoot();
		
		while(node!=null) {
			
			if(node.getElement().compareTo(element)==0) {
				return node;
			}
			
			if(node.getElement().compareTo(element)>0) {
				node = node.getLeft();
			}else {
				node = node.getRight();
			}
		}
		
		return node;
		
	}
	
	@Override
	public TreeNode<T> getRoot() {
		return this.root;
	}
	
	@Override
	public void setRoot(TreeNode<T> root) {
		this.root = root;
	}
}
