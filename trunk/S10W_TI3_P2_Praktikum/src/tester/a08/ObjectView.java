package tester.a08;

import java.awt.Dimension;
import java.awt.TextArea;

import javax.swing.JFrame;
import javax.swing.JSplitPane;
import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;

public class ObjectView extends JFrame {

	JTree tree = new JTree();
	DefaultMutableTreeNode node = new DefaultMutableTreeNode();
	TextArea text = new TextArea("Test");
	JSplitPane sp = new JSplitPane();
	
	public ObjectView() {
		sp.add(text, JSplitPane.RIGHT);
		sp.add(tree, JSplitPane.LEFT);
		add(sp);
		setPreferredSize(new Dimension(600, 480));
		pack();
			
	}
	
	public static void main(String[] args) {
		ObjectView ov = new ObjectView();
		ov.setVisible(true);
	}
}
