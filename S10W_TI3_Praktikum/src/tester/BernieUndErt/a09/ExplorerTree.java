package tester.BernieUndErt.a09;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTree;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeExpansionListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;

/**
 * In dieser Klasse befinden sich die Methoden, die ein ObjectExplorer 
 * Fenster �ffnen. Der Frame setzt sich aus einer gesplitteten Oberfl�che
 * f�r einen Objektbaum auf der Linken und Objekt/Methoden/Felderinformationen
 * auf der Rechten, sowie einem Men� zusammen.
 * 
 * @author Bernie und Ert         
 * @version 1.05 refactored from a03
 */
public class ExplorerTree {

	/**
	 * Innere Klasse (packagesichtbar), um sich Feld und Wert
	 * eines Objekts zu merken.
	 *  
	 * @author Bernie und Ert   
	 */
	 class FieldAndValue {
		final Field field;
		final Object value;

		public FieldAndValue(Field field, Object value) {
			this.field = field;
			this.value = value;
			;
		}
	}

	JFrame frame = new JFrame();
	private JTextArea fileInfoTextArea;
	private JTree tree;
	private JScrollPane scrollPane;
	private ObjectInspectHelper oih;
	
	
	//Konstruktor, Auswahl des zu inspizierenden Objekts
	//Geplant war, wie bei a03, ein PopUp beim Start des Programms, wor�ber man verschiedene Objekte
	//h�tte w�hlen k�nnen... wird vielleicht noch erg�nzt :)
	//TODO: Entweder mehrere Objekte im Baum realisieren oder "ObjectChooser" zur Laufzeit
	/**
	 * Konstruktor mit einigen Beispielobjekten, die inspiziert werden k�nnen.
	 * Es darf immer nur eine Zeile zur Zeit einkommentiert sein.
	 * Ggf. muss ArrayList noch importiert werden, ansonsten w�rde eine Warning erscheinen.
	 */
	public ExplorerTree() throws IllegalArgumentException, IOException, IllegalAccessException{
		this.oih= new ObjectInspectHelper();
//		Testobjekt1
//		Object objectToInspect = new JTree();
		
//		Testobjekt2
		Object objectToInspect = new DummyClass(5, 10);
		final ObjectHolder objectHolder = new ObjectHolder(objectToInspect);
		objectHolder.setObjectChangedListener(new ObjectChangedListener() {
			@Override
			public void objectChanged() throws Exception {
				DefaultMutableTreeNode rootNode = createRootNode(objectHolder.getObject());
				DefaultTreeModel model = new DefaultTreeModel(rootNode);
				tree.setModel(model);
			}
		});
		
		Thread objectHolderThread = new Thread(objectHolder, "objectHolderThread");
		objectHolderThread.start();
		
		this.scrollPane = new JScrollPane(buildExplorerTree(objectHolder));
		printAllThreads(getAllThreads());
	}

	/**
	 * Diese Methode erstellt den Hauptframe des Objektbrowsers und setzt wichtige Grundeinstellung. 
	 */
	public void buildFrame() {

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("1337 ObjectLister (c) Bernie & Ert");
		frame.setLayout(new BorderLayout());

		fileInfoTextArea = new JTextArea("Fileinfo:");

		JSplitPane splitPane = new JSplitPane();
		splitPane.setLeftComponent(scrollPane);
		splitPane.setRightComponent(fileInfoTextArea);

		frame.getContentPane().add(buildMenuBar(), BorderLayout.NORTH);
		frame.getContentPane().add(splitPane, BorderLayout.CENTER);

		frame.setVisible(true);
		frame.setExtendedState(Frame.MAXIMIZED_BOTH);
		frame.setMinimumSize(new Dimension(640, 480));
	}

	/**
	 * Diese Methode erstellt die Baumstruktur f�r unseren Objektbrowser.
	 * 
	 * @param objectHolder mit dem zu Inspizierenden Ojekt
	 * @return JTree Baum mit Fields und Methods des �bergabeobjekts
	 * @throws IOException
	 * @throws IllegalArgumentException
	 * @throws IllegalAccessException
	 */
	private JTree buildExplorerTree(ObjectHolder objectHolder) throws IOException, IllegalArgumentException, IllegalAccessException {
		DefaultMutableTreeNode rootNode = createRootNode(objectHolder.getObject());

		tree = new JTree(rootNode) {
	
			private static final long serialVersionUID = 1L;

			@Override
			public String convertValueToText(Object value, boolean selected,
					boolean expanded, boolean leaf, int row, boolean hasFocus) {
				DefaultMutableTreeNode node = (DefaultMutableTreeNode) value;
				Object userObject = node.getUserObject();
				if (userObject != null) {
					if (userObject instanceof FieldAndValue) {
						return ((FieldAndValue) userObject).field.getName();
					} else if (userObject instanceof Method) {
						return ((Method) userObject).getName();
					} else if (userObject.equals("Fields") || userObject.equals("Methods")) {
						return userObject.toString();
					} else {
						return userObject.getClass().getCanonicalName();
					}
				}
				return "";
			}
		};
		tree.addTreeSelectionListener(new TreeSelectionListener() {
			@Override
			public void valueChanged(TreeSelectionEvent e) {
				DefaultMutableTreeNode selectedNode = (DefaultMutableTreeNode) e.getPath().getLastPathComponent();
				Object userObject = selectedNode.getUserObject();
				
				try {
					fillTextAreaWithFileInfos(userObject);
				} catch (IllegalArgumentException e1) {
					e1.printStackTrace();
				} catch (IllegalAccessException e1) {
					e1.printStackTrace();
				}
			}
		});
		tree.addTreeExpansionListener(new TreeExpansionListener() {
			
			@Override
			public void treeExpanded(TreeExpansionEvent e) {
				DefaultMutableTreeNode node = (DefaultMutableTreeNode) e.getPath().getLastPathComponent();
				for (int i = 0; i < node.getChildCount(); i++) {
					DefaultMutableTreeNode currentNode = (DefaultMutableTreeNode) node.getChildAt(i);
					
					Object userObject = currentNode.getUserObject();
					if (userObject instanceof FieldAndValue) {
						FieldAndValue fav = (FieldAndValue) userObject;
						Field field = fav.field;
						Class<?> type = field.getType();
						if (!type.isPrimitive()) {
							try {
								addMethodsAndFields(currentNode, fav.value);
							} catch (IllegalArgumentException e1) {
								e1.printStackTrace();
							} catch (IllegalAccessException e1) {
								e1.printStackTrace();
							}
						}
					} else if (userObject instanceof Method) {
						Class<?> type = ((Method) userObject).getReturnType();
						if (!type.isPrimitive()) {
						}
					}
				}
			}

			@Override
			public void treeCollapsed(TreeExpansionEvent e) {
			}
		});

		return tree;
	}

	/**
	 * Hilfsmethode: Erstellt f�r die zu insp. Objekte nodes
	 * @param object �bergabeobjekt
	 * @return DefaultMutableTreeNode
	 * @throws IllegalAccessException
	 */
	private DefaultMutableTreeNode createRootNode(Object object) throws IllegalAccessException {
		DefaultMutableTreeNode rootDirNode = new DefaultMutableTreeNode(object);
		addMethodsAndFields(rootDirNode, object);
		return rootDirNode;
	}

	/**
	 * Diese Methode wird f�r das zu inspizierende Objekt aufgerufen und listet Felder und Methoden dazu auf.
	 * Weiterhin wird diese Methode gerufen, um f�r Objekttypen unterhalb unseres zu inspizierenden Objekts 
	 * Felder und Methoden zu listen.
	 * 
	 * @param parentNode �bergeordneter Node des Objekts
	 * @param objectToInspect urspr�ngliches zu inspizierndes Objekt
	 * @throws IllegalArgumentException
	 * @throws IllegalAccessException
	 */
	private void addMethodsAndFields(DefaultMutableTreeNode parentNode, Object objectToInspect) throws IllegalArgumentException, IllegalAccessException {
		DefaultMutableTreeNode fieldsChildNode = new DefaultMutableTreeNode("Fields");

		if (objectToInspect != null) {
			Field[] declaredFields = objectToInspect.getClass().getDeclaredFields();
			for (int i = 0; i < declaredFields.length; i++) {
				Field field = declaredFields[i];
				if (!field.isAccessible()) {
					field.setAccessible(true);
				}
				Object fieldValue = field.get(objectToInspect);
				FieldAndValue fav = new FieldAndValue(field, fieldValue);
				DefaultMutableTreeNode node = new DefaultMutableTreeNode(fav);
				fieldsChildNode.add(node);
			}
			
			if (fieldsChildNode.getChildCount() > 0) {
				parentNode.add(fieldsChildNode);
			}
	
			DefaultMutableTreeNode methodsChildNode = new DefaultMutableTreeNode("Methods");
			
			Method[] declaredMethods = objectToInspect.getClass().getDeclaredMethods();
			for (int i = 0; i < declaredMethods.length; i++) {
				DefaultMutableTreeNode node = new DefaultMutableTreeNode(declaredMethods[i]);
				methodsChildNode.add(node);
			}
			if (methodsChildNode.getChildCount() > 0) {
				parentNode.add(methodsChildNode);
			}
		}
	}

	/**
	 * Mit dieser Methode wird die Men�leiste des Objektbrowers erstellt.
	 * 
	 * @return JMenuBar Liefert die Men�leiste f�r den Objektbrowser 
	 */
	private JMenuBar buildMenuBar() {
		JMenuBar menuBar = new JMenuBar();
		JMenu data = new JMenu("Datei");
		JMenu help = new JMenu("Hilfe");
		final JMenuItem closeApp = new JMenuItem("Programm beenden");
		final JMenuItem aboutApp = new JMenuItem("�ber 1337-ObjectBrowser");

		ActionListener menuListener = new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				if (closeApp == event.getSource()) {
					System.exit(0);
				}

				if (aboutApp == event.getSource()) {
					buildAboutFrame();
				}
			}
		};

		closeApp.addActionListener(menuListener);
		aboutApp.addActionListener(menuListener);
		menuBar.add(data);
		menuBar.add(help);
		data.add(closeApp);
		help.add(aboutApp);

		return menuBar;
	}

	/**
	 * Methode zur Erstellung des About-Frames des Hilfedialogs der Men�leiste
	 */
	private void buildAboutFrame() {
		JTextArea aboutTxt = new JTextArea("Work done by:\nJan-Tristan Rudat\nMartin Slowikowski\n\n(c)1337-2010 Bernie und Ert");
		final JFrame aboutFrame = new JFrame("About 1337-ObjectLister");
		JButton exitButton = new JButton("Bump me!!!11eins");
		ActionListener exitListener = new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				aboutFrame.dispose();
			}
		};
		exitButton.addActionListener(exitListener);
		aboutFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		aboutFrame.setLocationRelativeTo(frame);
		aboutFrame.setSize(800, 300);
		aboutFrame.setResizable(false);
		aboutFrame.setLayout(new BorderLayout());
		aboutFrame.getContentPane().add(new JLabel(new ImageIcon("1337.gif")),	BorderLayout.WEST);
		aboutFrame.getContentPane().add(aboutTxt, BorderLayout.CENTER);
		aboutFrame.getContentPane().add(new JLabel(new ImageIcon("bernieert.jpg")), BorderLayout.EAST);
		aboutFrame.getContentPane().add(exitButton, BorderLayout.SOUTH);
		aboutFrame.setVisible(true);
	}

	/**
	 * In dieser Methode wird das Textfeld auf der rechten Seite der SplitPane mit entsprechenden Infos
	 * zu Methoden, Felder oder der Klasse gef�llt.
	 * 
	 * @param o �bergabeobjekt
	 * @throws IllegalArgumentException
	 * @throws IllegalAccessException
	 */
	private void fillTextAreaWithFileInfos(Object o) throws IllegalArgumentException, IllegalAccessException {
		StringBuilder sb = new StringBuilder();
		
		if (o instanceof FieldAndValue) {
			FieldAndValue fav = (FieldAndValue) o;
			sb.append("Feld:\n");
			sb.append(oih.printFieldInfos(fav));
		} else if (o instanceof Method) {
			sb.append("Methode:\n");
			sb.append(oih.printMethod((Method) o));
		} else if (!o.equals("Fields") && !o.equals("Methods")) {
			// Klasse
			sb.append("Klasse:\n");
			Class<?> c = o.getClass();
			sb.append("- Name: ").append(c.getSimpleName())
			.append("\n\n").append("- Class Modifier: ").append(oih.printClassModifiers(c)).append("\n\n")
			.append("- Oberklassen: ").append(oih.printSuperclasses(o)).append("\n")
			.append("- Interfaces (ggf. darunter Annotationen): ").append(oih.printInterfaces(o)).append("\n")
			.append("- Konstruktoren: ").append(oih.printConstructors(o)).append("\n")
			.append("- Annotationen: ").append(oih.printClassAnnotations(o)).append("\n");
		}

		fileInfoTextArea.setText(sb.toString());
	}

	/**
	 * source: http://nadeausoftware.com/articles/2008/04/java_tip_how_list_and_find_threads_and_thread_groups
	 * 
	 * @return
	 */
	static Thread[] getAllThreads( ) {
	    final ThreadGroup root = getRootThreadGroup( );
	    final ThreadMXBean thbean = ManagementFactory.getThreadMXBean( );
	    int nAlloc = thbean.getThreadCount( );
	    int n = 0;
	    Thread[] threads;
	    do {
	        nAlloc *= 2;
	        threads = new Thread[ nAlloc ];
	        n = root.enumerate( threads, true );
	    } while ( n == nAlloc );
	    return java.util.Arrays.copyOf( threads, n );
	}
	

	 
	/**
	 * source: http://nadeausoftware.com/articles/2008/04/java_tip_how_list_and_find_threads_and_thread_groups
	 * 
	 * @return
	 */
	static ThreadGroup getRootThreadGroup( ) {
		ThreadGroup rootThreadGroup = null;
	    if ( rootThreadGroup != null )
	        return rootThreadGroup;
	    ThreadGroup tg = Thread.currentThread( ).getThreadGroup( );
	    ThreadGroup ptg;
	    while ( (ptg = tg.getParent( )) != null )
	        tg = ptg;
	    return tg;
	}
	
	/**
	 * @param threads
	 */
	static void printAllThreads(Thread[] threads) {
		for(Thread thr : threads) {
			System.out.println(thr);
		}
	}

}