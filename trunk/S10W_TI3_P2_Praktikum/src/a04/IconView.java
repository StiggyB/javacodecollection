package a04;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 04<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, PR2 Praktikum
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

import java.awt.Dimension;
import java.awt.GraphicsEnvironment;
import java.awt.Point;
import java.awt.Rectangle;

import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
/**
 * Diese Klasse bildet die View, welche 
 * Veraenderungen des IconModels anzeigt.
 *
 */

public class IconView {
	
	private JFrame frame;
	
	public JFrame getFrame() {
		return frame;
	} //getFrame

	public void setFrame(JFrame frame) {
		this.frame = frame;
	} //setFrame

	/**
	 * Diese Methode erstellt das Frame,
	 * welche die Umgebung der Labels vorgibt.
	 * 
	 * @param model	zum hinzufuegen der Labels
	 * @exception UnsopportedLookAndFeelException
	 */
	public void showIcons(IconModel model) {
    	try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnsupportedLookAndFeelException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} //catch
    	
    	frame = new JFrame();
    	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	frame.setLayout(null);
    	frame.setUndecorated(true);
    	Rectangle rect = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
    	frame.setPreferredSize(new Dimension(rect.width, rect.height));
    	frame.setResizable(false);
    	for(IconLabel label : model.getLabelList()) {
    		frame.add(label);
    	} //for
    	frame.setLocation(new Point(0,0));
    	frame.setVisible(true);
    	frame.pack();
    } //showIcons
} //IconView
