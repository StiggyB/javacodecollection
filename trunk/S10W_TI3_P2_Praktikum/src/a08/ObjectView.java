package a08;

import java.awt.Dimension;
import java.awt.GraphicsEnvironment;
import java.awt.Rectangle;
import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;

import javax.swing.JFrame;
//import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTree;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeExpansionListener;
import javax.swing.tree.DefaultMutableTreeNode;

public class ObjectView {
	
	private JTree tree;
	private JTextArea ObjectInfo;
//	private JScrollPane jsp;
	private JFrame frame;
	private ObjectBrowser ob;
	
	public ObjectView(Object obj) {
		
		//TODO Extract to create-Methods
		if(obj != null) {
		ob = new ObjectBrowser();
		ob.searchThroughClass();
		try {
			ob.reflectObject(obj);
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
		DefaultMutableTreeNode root = new DefaultMutableTreeNode(obj);
		for(Field Info : ob.getFields()) {
			DefaultMutableTreeNode node = new DefaultMutableTreeNode(Info);
			root.add(node);
		}
		
		tree = new JTree(root);
		tree.addTreeExpansionListener(new TreeExpansionListener() {

			@Override
			public void treeCollapsed(TreeExpansionEvent event) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void treeExpanded(TreeExpansionEvent event) {
				// TODO Auto-generated method stub
				
			}

			
		});
		
		ObjectInfo = new JTextArea("ObjectInfo: ");
		StringBuilder sb = new StringBuilder();
		for(Annotation ann : ob.getAnnotations()) {
			sb.append(ann.getClass().getCanonicalName());
		}
		
		//TODO Why Proxy3 ... TestAnno must be
		ObjectInfo.setText(sb.toString());
		
		JSplitPane sp = new JSplitPane();
		sp.setLeftComponent(tree);
		sp.setRightComponent(ObjectInfo);
		
		frame = new JFrame("ObjectBrowser");
    	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	Rectangle rect = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
    	frame.setPreferredSize(new Dimension(rect.width, rect.height));
		frame.add(sp);
		frame.setVisible(true);
		frame.pack();
		}
	}

	
	
//	public JTree createObejctTree(Object obj) {
//		return JTree tre;
//	}

	
	
}
