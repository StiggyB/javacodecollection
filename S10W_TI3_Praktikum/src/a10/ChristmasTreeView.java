package a10;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 10<br>
 * 
 * Version: V0<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, HTML Elements by Martin Slowikowski
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

import java.awt.Dimension;
import java.awt.GraphicsEnvironment;
import java.awt.Rectangle;

import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JScrollPane;

/**
 * This class builds the View 
 * from the Christmas Tree Pattern.
 *
 */
public class ChristmasTreeView {

	
	/**
	 * This constructor creates all GUI
	 * components and work with HTML-Tags.
	 * 
	 * @param chrisTree reference to the pattern
	 * @param n count of bits
	 */
	public ChristmasTreeView(ChristmasTreePattern chrisTree, int n) {
		
		JFrame frame = new JFrame("ChristmasTreePattern");
		
		String treeStr = chrisTree.createChrisTree(n).toString();
		JEditorPane editTree = new JEditorPane();
		editTree.setContentType("text/html");
		editTree.setEditable(false);
		editTree.setText(treeStr);
		JScrollPane jsp = new JScrollPane(editTree);

		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Rectangle rect = GraphicsEnvironment.getLocalGraphicsEnvironment()
				.getMaximumWindowBounds();
		frame.setPreferredSize(new Dimension(rect.width, rect.height));
		frame.add(jsp);
		frame.setVisible(true);
		frame.pack();
	}
	
}
