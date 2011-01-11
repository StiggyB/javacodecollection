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

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 * This class holds the main method and 
 * exists as point of entry.
 *
 */
public class MainApp {

	/**
	 * Main method to start the ObjectBrowser application
	 * in a specific Thread.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
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
			Thread objThread = new Thread(new ObjectApp(), "ObjectAppThread");
			objThread.start();
//			System.out.println(Thread.currentThread());
	}
}
