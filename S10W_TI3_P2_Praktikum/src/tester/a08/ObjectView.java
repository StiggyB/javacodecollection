package tester.a08;

import java.awt.Dimension;
import java.awt.GraphicsEnvironment;
import java.awt.Rectangle;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;


public class ObjectView {
	
	private JTree tree;
	private JTextArea objectInfo;
	private JFrame frame;
	private ObjectBrowser ob;
	private Object obj;
	private Object testObj;
	
	public ObjectView(Object obj) {
		
		//TODO RootNode have to implement toString
		if(obj != null) {
		this.obj = obj;
		testObj = null;
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
		createObjectProperties(root);
		
		
		tree = new JTree(root);
		/*
		tree.addTreeWillExpandListener(new TreeWillExpandListener() {

			@Override
			public void treeWillCollapse(TreeExpansionEvent e)
					throws ExpandVetoException {
			}

			@Override
			public void treeWillExpand(TreeExpansionEvent e)
					throws ExpandVetoException {
				// 
				TreePath path = e.getPath();
		        DefaultMutableTreeNode node = (DefaultMutableTreeNode) path.getLastPathComponent();
		        String data = node.getUserObject().toString();
//		        System.out.println(data);
//				ob.zoomInField(fld);
			}
			
		});
		*/
		tree.addTreeSelectionListener(new TreeSelectionListener() {

			@Override
			public void valueChanged(TreeSelectionEvent e) {
//				System.out.println(e.getPath().getLastPathComponent());
				DefaultMutableTreeNode node = (DefaultMutableTreeNode)
                tree.getLastSelectedPathComponent();
				if (node == null) {
					return;
				}
				Object nodeInfo = node.getUserObject();
				StringBuilder sb = new StringBuilder();
				if(nodeInfo instanceof String) {
					sb.append(nodeInfo.toString());
				} else if(nodeInfo instanceof Field) {
					try {
						Field fld = (Field) nodeInfo;
						if(fld.getType().isPrimitive()) {
							sb = ob.zoomInField(fld, obj);
						} else {
							ob.searchThroughClass();
							System.out.println(fld);
							System.out.println(fld.getType());
							System.out.println(fld.getClass());
							if (testObj == null) {
								testObj = obj;
							}
								//Danger Inner Class obj here
							//vorher in will oder expandListener auslagern
							 //wenn ich den Node verlasse setzw testObj == null!!!
							fld.setAccessible(true);
							System.out.println(testObj);
							Object typeObj = ObjectBrowser.as(fld.get(testObj), fld.getType()); //obj == a08.Clazz
							ob.reflectObject(fld.get(testObj));
							
							createObjectProperties(node);
							sb = ob.zoomInField(fld, testObj);
							testObj = typeObj;
						}
					} catch (IllegalArgumentException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (IllegalAccessException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				} else if(nodeInfo instanceof Method) {
					try {
						sb = ob.zoomInMethod((Method)nodeInfo, obj);
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
					sb = ob.getClassInfo((Object)nodeInfo);
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



/*
 else {
						ob.searchThroughClass();
						System.out.println(fld);
						System.out.println(fld.getType());
						System.out.println(fld.getClass());
						if (testObj == null) {
							testObj = obj;
						}
							//Danger Inner Class obj here
						//vorher in will oder expandListener auslagern
						//Methoden die vererbt sind aussortieren
						 //wenn ich den Node verlasse setzw testObj == null!!!
						fld.setAccessible(true);
						System.out.println(testObj);
						Object typeObj = ObjectBrowser.as(fld.get(testObj), fld.getType()); //obj == a08.Clazz
						ob.reflectObject(fld.get(testObj));
						
						createObjectProperties(node);
						sb = ob.zoomInField(fld, testObj);
						testObj = typeObj;
					}
				} catch (IllegalArgumentException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (IllegalAccessException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
 */

/*
tree.addTreeExpansionListener(new TreeExpansionListener() {

@Override
public void treeCollapsed(TreeExpansionEvent e) {
}

@Override
public void treeExpanded(TreeExpansionEvent e) {

DefaultMutableTreeNode node = (DefaultMutableTreeNode)
e.getPath().getLastPathComponent();

if (node == null) {
	return;
}
Object typeObj = null;
for(int i = 0; i < node.getChildCount(); i++) {
	System.out.println(node + " NODE !");
	DefaultMutableTreeNode trNode = (DefaultMutableTreeNode) node.getParent();
	System.out.println(trNode.getUserObject() + "OBJ");
	Object trObj = trNode.getUserObject();
	DefaultMutableTreeNode testNode = (DefaultMutableTreeNode) node.getChildAt(i);
	
	Object nodeInfo = testNode.getUserObject(); //obj change to testObj last change
	StringBuilder sb = new StringBuilder();
	
//	if(nodeInfo instanceof String) {
//		System.out.println(testObj);
//		sb.append(testObj.toString());
//	} else 
	if(nodeInfo instanceof Field) {
		try {
			Field testFld = (Field) nodeInfo;
			testFld.setAccessible(true);
			Class<?> typeObj2 = testFld.getType();
			if(!(typeObj2.isPrimitive())) {
//				System.out.println("TRUE");
				System.out.println(nodeInfo + " IN IT");
//						Object nodeInfo = testNode.getUserObject();
//						if(nodeInfo instanceof Field) {
				
//				System.out.println(obj + " Passed");
				Field fld = (Field) nodeInfo;
				
				ob.searchThroughClass();
//				System.out.println(expFld);
//				System.out.println(expFld.getType());
//				System.out.println(expFld.getClass());
				if (testObj == null) {
					System.out.println("Test == Null");
					testObj = obj;
				}
					//Danger Inner Class obj here
				//Methoden die vererbt sind aussortieren
				 //wenn ich den Node verlasse setzw testObj == null!!!
				fld.setAccessible(true);
				System.out.println(fld);
				System.out.println(testObj + "OBJ");
				System.out.println(fld.getType());
			

				typeObj = ObjectBrowser.as(fld.get(trObj), fld.getType()); //Error -- Can not set final [C field java.lang.String.value to a08.Clazz
																				//testObj setted wrong!!! General think about testObj = typeObj!!!
				//obj == a08.Clazz
				System.out.println(fld.get(testObj));
				if(testObj != null) {
					ob.reflectObject(fld.get(testObj)); //null.getClass = null ...
//					System.out.println("TEST");
					createObjectProperties(testNode);
//					objectInfo.setText(ob.zoomInField(fld, testObj).toString());
				 }
				
				testObj = null;
			}
		} catch (IllegalArgumentException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (IllegalAccessException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}
		
		System.out.println(i);
		
}
System.out.println(typeObj + " Type");
testObj = typeObj;
}*/

/*
//UNDER EXPANDLISTENER CODE

System.out.println(node.getUserObject());
Object expObj = e.getSource();
Object nodeInfo = node.getUserObject();
Field fld = (Field) expObj;

ob.searchThroughClass();
System.out.println(fld);
System.out.println(fld.getType());
System.out.println(fld.getClass());
if (testObj == null) {
testObj = obj;
}
//Danger Inner Class obj here
//vorher in will oder expandListener auslagern
//Methoden die vererbt sind aussortieren
//wenn ich den Node verlasse setzw testObj == null!!!
fld.setAccessible(true);
System.out.println(testObj);
Object typeObj;
try {
typeObj = ObjectBrowser.as(fld.get(testObj), fld.getType());
//obj == a08.Clazz
ob.reflectObject(fld.get(testObj));

createObjectProperties(node);
testObj = typeObj;
objectInfo.setText(ob.zoomInField(fld, testObj).toString());
} catch (IllegalArgumentException e1) {
// TODO Auto-generated catch block
e1.printStackTrace();
} catch (IllegalAccessException e1) {
// TODO Auto-generated catch block
e1.printStackTrace();
}*/

/*
tree.addTreeSelectionListener(new TreeSelectionListener() {

		@Override
		public void valueChanged(TreeSelectionEvent e) {
//			System.out.println(e.getPath().getLastPathComponent());
//			System.out.println(tree.getLastSelectedPathComponent());
			DefaultMutableTreeNode node = (DefaultMutableTreeNode)
            tree.getLastSelectedPathComponent();
			if (node == null) {
				return;
			}
			
			System.out.println(node.getUserObject() + " uObj");
			Object nodeInfo = node.getUserObject();
			DefaultMutableTreeNode parentNode = null;
			Object parentInfo = null;
			if(node.getParent() != null) {
				
				ob.reflectObject(obj); //If root new reflection
//				System.out.println(node);
//				System.out.println(node.getParent());
//				System.out.println(node.getParent().getParent());
				node = (DefaultMutableTreeNode) node.getParent().getParent();
				if(node != null) {
					System.out.println("parentParent");
					System.out.println(node);
					parentInfo = node.getUserObject();
					System.out.println(parentInfo);
				}
			}
			if(parentInfo == null) {
				System.out.println(nodeInfo);
				parentInfo = nodeInfo;
			}
			StringBuilder sb = new StringBuilder();
			if(nodeInfo instanceof String) {
				sb.append(nodeInfo.toString());
			} else if(nodeInfo instanceof Field) {
				Field fld = (Field) nodeInfo;
				if(fld.getType().isPrimitive()) {
					try {
						
						System.out.println(parentInfo + " bevor!"); //java.lang.String a08.Clazz.str bevor!
																	//private final int java.lang.String.offset
						System.out.println(fld);
						System.out.println(nodeInfo);			//--
//						System.out.println(fld.get(parentInfo));
						
						sb = ob.zoomInField(fld, parentInfo);  //Error -- Can not set int field java.lang.String.hash to java.lang.reflect.Field
					} catch (IllegalArgumentException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (IllegalAccessException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				} else {
					try {
						System.out.println(fld);
//						System.out.println(obj);
//						System.out.println(nodeInfo.getClass().getCanonicalName() + " nodeInfo");
//						System.out.println(fld.get(parentInfo));
						System.out.println(parentInfo + " ReferenceType!");
//						System.out.println(fld.get(parentNode.getUserObject()));
//						if((fld.getType().isArray())) {
//						sb = ob.zoomInField(fld, null);
//						} else {
						sb = ob.zoomInField(fld, parentInfo); //Error parentInfo -- Can not set final [C field java.lang.String.value to java.lang.reflect.Field
//						}
//						sb = ob.zoomInField(fld, nodeInfo.getClass().getCanonicalName()); //TESTEN !!! String Node geht nicht
//						sb = ob.zoomInField(fld, obj);
//						sb = ob.zoomInField(fld, testObj);
						objectInfo.setText(sb.toString());
					} catch (IllegalArgumentException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (IllegalAccessException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			} else if(nodeInfo instanceof Method) {
				try {
					sb = ob.zoomInMethod((Method)nodeInfo, parentInfo);
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
				System.out.println("IS Class");
				
				sb = ob.getClassInfo((Object)nodeInfo);
			}
			objectInfo.setText(sb.toString());
			
//			objectInfo.setText(nodeInfo.toString());

		}
		
	});
*/