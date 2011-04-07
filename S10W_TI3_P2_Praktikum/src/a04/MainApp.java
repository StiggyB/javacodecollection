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

import java.io.IOException;

/**
 * Diese Klasse startet die gesamte Anwendung.
 *
 */
public class MainApp {

	public static void main(String[] args) throws IOException {
		IconModel model = new IconModel();
		model.init();
		IconView view = new IconView();
		view.showIcons(model);
		model.run(view); 		//"Weak typed" durch Objekt

	} //main
} //MainApp
