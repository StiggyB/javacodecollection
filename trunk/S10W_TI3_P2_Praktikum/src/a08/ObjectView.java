package a08;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 08<br>
 * 
 * Version: V0<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, PR2 Praktikum
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

import java.awt.Dimension;
import java.awt.GraphicsEnvironment;
import java.awt.Rectangle;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTree;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeExpansionListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;

public class ObjectView {
	
	private JTree tree;
	private JTextArea objectInfo;
	private JFrame frame;
	private ObjectBrowser ob;
	private Object obj;
	
	public ObjectView(Object obj) {	
		if(obj != null) {
		this.obj = obj;
		this.ob = new ObjectBrowser(this.obj);
		this.ob.searchThroughClass();
		try {
			this.ob.reflectObject(obj);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		createObejctTree();
		createObjectFrame();
		} else {
			JOptionPane
			.showMessageDialog(
					null,
					"Error: Object is null. Please change the Object to inspect.",
					"Null Error", JOptionPane.WARNING_MESSAGE);
		}
	}

	/**
	 * Source: http://www.java2s.com/Tutorial/Java/0240__Swing/TreeWillExpandListener.htm
	 * 		   http://www.dil.univ-mrs.fr/~garreta/docJava/tutorial/uiswing/events/treeselectionlistener.html
	 */
	private void createObejctTree() {
		DefaultMutableTreeNode root = new DefaultMutableTreeNode(this.obj);
		createObjectProperties(root);
		
		tree = new JTree(root);
		tree.addTreeExpansionListener(new TreeExpansionListener() {

			@Override
			public void treeCollapsed(TreeExpansionEvent e) {
			}

			@Override
			public void treeExpanded(TreeExpansionEvent e) {			
				DefaultMutableTreeNode accNode = (DefaultMutableTreeNode)
                e.getPath().getLastPathComponent();
				DefaultMutableTreeNode treeNode = (DefaultMutableTreeNode) accNode.getParent();
				Object treeObj = treeNode.getUserObject();						//Object from ParentNode for the fld.get(obj);
				
				if (accNode == null) {
					return;
				}
				for(int i = 0; i < accNode.getChildCount(); i++) {	
					DefaultMutableTreeNode childNode = (DefaultMutableTreeNode) accNode.getChildAt(i);	
					Object childObj = childNode.getUserObject(); 				//Object to Test 	
					
					if(childObj instanceof Field) {
							Field accFld = (Field) childObj;
							accFld.setAccessible(true);
							if(!(accFld.getType().isPrimitive())) {							
								Field fld = (Field) childObj;
								fld.setAccessible(true);
								ob.searchThroughClass();
								if(treeObj != null) {
									if((fld.getType().isArray())) {
										ob.reflectObject(null);
									} else {
										try {
										ob.reflectObject(fld.get(treeObj));
									} catch (IllegalArgumentException e1) {
										// TODO Auto-generated catch block
										e1.printStackTrace();
									} catch (IllegalAccessException e1) {
										// TODO Auto-generated catch block
										e1.printStackTrace();
									}
									createObjectProperties(childNode);
								}	
							}
						}	
					}
				}
			}
		});
			
		tree.addTreeSelectionListener(new TreeSelectionListener() {

			@Override
			public void valueChanged(TreeSelectionEvent e) {
				DefaultMutableTreeNode node = (DefaultMutableTreeNode)
                tree.getLastSelectedPathComponent();
				if (node == null) {
					return;
				}
				Object nodeObj = node.getUserObject();
				Object parentObj = node.getUserObject();
				if(node.getParent() != null) {
					DefaultMutableTreeNode parentNode = (DefaultMutableTreeNode) node.getParent().getParent();
					if(parentNode != null) {
						parentObj = parentNode.getUserObject();
					}
				}
				StringBuilder sb = new StringBuilder();
				if(nodeObj instanceof String) {
					sb.append(nodeObj.toString());
				} else if(nodeObj instanceof Field) {
					Field fld = (Field) nodeObj;
					if(fld.getType().isPrimitive()) {
						try {							
							sb = ob.zoomInField(fld, parentObj); 
						} catch (IllegalArgumentException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						} catch (IllegalAccessException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
					} else {
						try {
							sb = ob.zoomInField(fld, parentObj);
						} catch (IllegalArgumentException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						} catch (IllegalAccessException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
					}
				} else if(nodeObj instanceof Method) {
					try {
						sb = ob.zoomInMethod((Method)nodeObj, parentObj);
					} catch (IllegalArgumentException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (IllegalAccessException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (InvocationTargetException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				} else {
					ob.reflectObject(nodeObj);
					sb = ob.getClassInfo((Object)nodeObj);
				}
				objectInfo.setText(sb.toString());
			}
		});
	}
	
	private void createObjectProperties(DefaultMutableTreeNode root) {
		DefaultMutableTreeNode fldNode = new DefaultMutableTreeNode("Field");
		for(Field fld : ob.getFields()) {
			DefaultMutableTreeNode fldChild = new DefaultMutableTreeNode(fld);
			fldNode.add(fldChild);
		}
		root.add(fldNode);
		DefaultMutableTreeNode metNode = new DefaultMutableTreeNode("Method");
		for(Method met : ob.getMethods()) {
			DefaultMutableTreeNode metChild = new DefaultMutableTreeNode(met);
			metNode.add(metChild);
		}
		root.add(metNode);
	}
	
	private void createObjectFrame() {
		objectInfo = new JTextArea("ObjectInfo: ");	
		JSplitPane sp = new JSplitPane();
		JScrollPane jsp = new JScrollPane(tree);
		
		
		sp.add(objectInfo, JSplitPane.RIGHT);
		sp.add(jsp, JSplitPane.LEFT);
		sp.setDividerLocation(300);
		
		frame = new JFrame("ObjectBrowser");
    	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	Rectangle rect = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
    	frame.setPreferredSize(new Dimension(rect.width, rect.height));
		frame.add(sp);
		frame.setVisible(true);
		frame.pack();	
	}
}