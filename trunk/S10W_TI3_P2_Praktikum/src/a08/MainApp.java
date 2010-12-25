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
		// TODO How to filter getX methods without getDeclaredX ?
		// TODO How to iterate sync with the data structure of Arrays ?
		
		ObjectBrowser ob = new ObjectBrowser();
//		ob.searchContent(ob.setObject(new Clazz(1)));
		ob.searchThroughClass();
		ob.reflectObject(new Clazz());
		

	}
}
