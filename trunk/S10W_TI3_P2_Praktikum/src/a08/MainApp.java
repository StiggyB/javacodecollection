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

import a05.RingBufferTest;
import tester.a08.Clazz;

public class MainApp {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO searchAnnotations() result null
		
		ObjectBrowser ob = new ObjectBrowser();
		ob.searchContent(ob.setObject(new Clazz(1)));
		

	}
}
