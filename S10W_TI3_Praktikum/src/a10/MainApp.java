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

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 * This class includes the main-method
 * and starts the Application.
 *
 */
public class MainApp {

	/**
	 * This Main-method starts the Application
	 * and sets the count of  bits.
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
		
		//Set the number of bits here!
		new ChristmasTreeView(new ChristmasTreePattern(), 8);
	}
	
}
