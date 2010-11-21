package a04;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 04<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing
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

public class ShowInFrame {
	
	private static JFrame frame;

    public static JFrame getFrame() {
		return frame;
	}

	public static void setFrame(JFrame frame) {
		ShowInFrame.frame = frame;
	}

	public static void showIcons() {
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
		}
    	
    	frame = new JFrame();

    	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	frame.setLayout(null);
    	frame.setBounds(0, 0, 800, 600);
    	frame.setUndecorated(true);


//    	Rectangle rect = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
//    	frame.setPreferredSize(new Dimension(rect.width, rect.height));
    	frame.setResizable(false);
    	for(IconLabel label : IconModel.getList()) {
    		frame.add(label);
    	}
    	frame.setLocation(new Point(0,0));
    	frame.setVisible(true);
//    	frame.pack();
    }
}
