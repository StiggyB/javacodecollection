package a09;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 09<br>
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

/**
 * This class build the View of the a09.ObjectBrowser.
 * It holds a TextArea with the specific properties
 * and a Pane with the Tree to navigate.
 * Additional two listener implemented, which
 * coordinate the expansions and selections in the Tree
 *
 */
public class ObjectView {

	private JTree tree;
	private JTextArea objectInfo;
	private JFrame frame;
	private ObjectBrowser ob;
	private Object obj;

	/**
	 * The constructor sets a09.ObjectView.obj
	 * with obj.
	 * The model ObjectBrowser starts and the
	 * initial methods call here.
	 * 
	 * @param obj
	 * @see a09.ObjectBrowser#searchThroughClass
	 * @see a09.ObjectBrowser#reflectObject
	 */
	public ObjectView(Object obj) {
		if (obj != null) {
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
	 * This method creates the Tree to navigate through
	 * the Object properties.
	 * Two Listener added: TreeExpandListener and TreeSelectionListener.
	 * The necessary methods implemented in two inner classes.
	 * 
	 * @see java.util.EventListener.TreeExpansionListener
	 * @see java.util.EventListener.TreeSelectionListener
	 * source:
	 * http://www.java2s.com/Tutorial/Java/0240__Swing/TreeWillExpandListener
	 * .htm http://www.dil.univ-mrs.fr/~garreta/docJava/tutorial/uiswing/events/
	 * treeselectionlistener.html
	 */
	private void createObejctTree() {
		DefaultMutableTreeNode root = new DefaultMutableTreeNode(this.obj);
		createObjectProperties(root);

		tree = new JTree(root);
		tree.addTreeExpansionListener(new TreeExpansionListener() {

			/*
			 * (non-Javadoc) 
			 * This method normally must close created nodes by the expansion
			 * 
			 * @see
			 * javax.swing.event.TreeExpansionListener#treeCollapsed(javax.swing
			 * .event.TreeExpansionEvent)
			 */
			@Override
			public void treeCollapsed(TreeExpansionEvent e) {

			}

			/*
			 * (non-Javadoc) 
			 * This method has not implemented the expansion for
			 * methods (same as fields)
			 * 
			 * @see
			 * javax.swing.event.TreeExpansionListener#treeExpanded(javax.swing
			 * .event.TreeExpansionEvent)
			 */
			@Override
			public void treeExpanded(TreeExpansionEvent e) {
				DefaultMutableTreeNode accNode = (DefaultMutableTreeNode) e
						.getPath().getLastPathComponent();
				DefaultMutableTreeNode treeNode = (DefaultMutableTreeNode) accNode
						.getParent();
				Object treeObj = treeNode.getUserObject(); // Object from
															// ParentNode for
															// fld.get(object);
				if (accNode == null) {
					return;
				}
				for (int i = 0; i < accNode.getChildCount(); i++) {
					DefaultMutableTreeNode childNode = (DefaultMutableTreeNode) accNode
							.getChildAt(i);
					Object childObj = childNode.getUserObject(); // Object to
																	// Test
					if (childObj instanceof Field) {
						Field accFld = (Field) childObj;
						accFld.setAccessible(true);
						if (!(accFld.getType().isPrimitive())) {
							Field fld = (Field) childObj;
							fld.setAccessible(true);
							ob.searchThroughClass();
							if (treeObj != null) {
								if ((fld.getType().isArray())) {
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

			/*
			 * (non-Javadoc) 
			 * This Method reacts by any selection and update it
			 * 
			 * @see
			 * javax.swing.event.TreeSelectionListener#valueChanged(javax.swing
			 * .event.TreeSelectionEvent)
			 */
			@Override
			public void valueChanged(TreeSelectionEvent e) {
				DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree
						.getLastSelectedPathComponent();
				if (node == null) {
					return;
				}
				Object nodeObj = node.getUserObject();
				Object parentObj = node.getUserObject();
				if (node.getParent() != null) {
					DefaultMutableTreeNode parentNode = (DefaultMutableTreeNode) node
							.getParent().getParent();
					if (parentNode != null) {
						parentObj = parentNode.getUserObject();
					}
				}
				StringBuilder sb = new StringBuilder();
				if (nodeObj instanceof String) {
					sb.append(nodeObj.toString());
				} else if (nodeObj instanceof Field) {
					Field fld = (Field) nodeObj;
					if (fld.getType().isPrimitive()) {
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
				} else if (nodeObj instanceof Method) {
					try {
						sb = ob.zoomInMethod((Method) nodeObj, parentObj);
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
					sb = ob.getClassInfo(obj);
				}
				objectInfo.setText(sb.toString());
			}
		});
	}

	/**
	 * This method creates the field and method nodes
	 * to expand the Tree.
	 * 
	 * @param root
	 */
	private void createObjectProperties(DefaultMutableTreeNode root) {
		DefaultMutableTreeNode fldNode = new DefaultMutableTreeNode("Field");
		for (Field fld : ob.getFields()) {
			DefaultMutableTreeNode fldChild = new DefaultMutableTreeNode(fld);
			fldNode.add(fldChild);
		}
		root.add(fldNode);
		DefaultMutableTreeNode metNode = new DefaultMutableTreeNode("Method");
		for (Method met : ob.getMethods()) {
			DefaultMutableTreeNode metChild = new DefaultMutableTreeNode(met);
			metNode.add(metChild);
		}
		root.add(metNode);
	}

	/**
	 * This method creates the frame of the ObjectBrowser.
	 * It holds a TextArea with the specific properties
	 * and a Pane with the Tree to navigate.
	 * 
	 */
	private void createObjectFrame() {
		objectInfo = new JTextArea("ObjectInfo: ");
		JSplitPane sp = new JSplitPane();
		JScrollPane jsp = new JScrollPane(tree);

		sp.add(objectInfo, JSplitPane.RIGHT);
		sp.add(jsp, JSplitPane.LEFT);
		sp.setDividerLocation(300);

		frame = new JFrame("ObjectBrowser");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Rectangle rect = GraphicsEnvironment.getLocalGraphicsEnvironment()
				.getMaximumWindowBounds();
		frame.setPreferredSize(new Dimension(rect.width, rect.height));
		frame.add(sp);
		frame.setVisible(true);
		frame.pack();
	}
}