package a08;

import java.awt.Dimension;
import java.awt.GraphicsEnvironment;
import java.awt.Rectangle;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import javax.swing.JFrame;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTree;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.event.TreeWillExpandListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.ExpandVetoException;
import javax.swing.tree.TreePath;

public class ObjectView {
	
	private JTree tree;
	private JTextArea ObjectInfo;
//	private JScrollPane jsp;
	private JFrame frame;
	private ObjectBrowser ob;
	private Object obj;
	
	public ObjectView(Object obj) {
		
		//TODO
		if(obj != null) {
		this.obj = obj;
		this.ob = new ObjectBrowser();
		this.ob.searchThroughClass();
		try {
			this.ob.reflectObject(obj);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		createObejctTree();
		createObjectFrame();
		} else {
			System.err.println("Object is null.");
		}
	}

	
	
	/**
	 * Source: http://www.java2s.com/Tutorial/Java/0240__Swing/TreeWillExpandListener.htm
	 * 		   http://www.dil.univ-mrs.fr/~garreta/docJava/tutorial/uiswing/events/treeselectionlistener.html
	 */
	private void createObejctTree() {
		DefaultMutableTreeNode root = new DefaultMutableTreeNode(this.obj);
		DefaultTreeModel model = new DefaultTreeModel(root);
		DefaultMutableTreeNode fldNode = new DefaultMutableTreeNode("Fields");
		DefaultMutableTreeNode metNode = new DefaultMutableTreeNode("Methods");
		root.add(fldNode);
		root.add(metNode);
		
		
		tree = new JTree(model);
		//TODO Listener have to implement - Fields / Methods - TextArea
		tree.addTreeWillExpandListener(new TreeWillExpandListener() {

			@Override
			public void treeWillCollapse(TreeExpansionEvent e)
					throws ExpandVetoException {
				// TODO Auto-generated method stub
//				JTree tree = (JTree) e.getSource();
//				DefaultMutableTreeNode newNode;
			}

			@Override
			public void treeWillExpand(TreeExpansionEvent e)
					throws ExpandVetoException {
				// TODO Auto-generated method stub
				TreePath path = e.getPath();
		        DefaultMutableTreeNode node = (DefaultMutableTreeNode) path.getLastPathComponent();
		        String data = node.getUserObject().toString();
		        System.out.println(data);
				
			}
			
		});
		
		tree.addTreeSelectionListener(new TreeSelectionListener() {

			@Override
			public void valueChanged(TreeSelectionEvent e) {
				// TODO Auto-generated method stub
				System.out.println(e.getPath().getLastPathComponent());
				DefaultMutableTreeNode node = (DefaultMutableTreeNode)
                tree.getLastSelectedPathComponent();
				System.out.println(node);
				if (node == null) {
					return;
				}
				Object nodeInfo = node.getUserObject();
				StringBuilder sb;
				if(nodeInfo instanceof Field) {
					sb = ob.zoomInField((Field)nodeInfo);
				}
				else if(nodeInfo instanceof Method) {
					sb = ob.zoomInMethod((Method)nodeInfo);
				} else {
					sb = ob.getClassInfo((Object)nodeInfo);
				}
				ObjectInfo.setText(sb.toString());
			}
		
		});
	}

	
	private void createObjectFrame() {
		ObjectInfo = new JTextArea("ObjectInfo: ");
		
		JSplitPane sp = new JSplitPane();
		
		sp.add(ObjectInfo, JSplitPane.RIGHT);
		sp.add(tree, JSplitPane.LEFT);
		sp.setDividerLocation(150);
		
		frame = new JFrame("ObjectBrowser");
    	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	Rectangle rect = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
    	frame.setPreferredSize(new Dimension(rect.width, rect.height));
		frame.add(sp);
		frame.setVisible(true);
		frame.pack();
		
	}
	
}
