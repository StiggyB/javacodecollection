package a04;

import java.io.IOException;

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

public class MainApp {

	public static void main(String[] args) throws IOException {
		IconModel model = new IconModel();
		model.init();
		IconView view = new IconView();
		view.showIcons(model);
		model.run(view); 		//"Weak typed" durch Objekt

		// TODO write JavaDoc
	}
}
