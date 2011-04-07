package tester.a10;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 * Startklasse f�r eine grafische Oberfl�che mit dem ChristmasTreePattern des
 * n-ten Grades.
 * 
 * @author Bernie und Ert
 * @version 1.0
 */
public class MainApp {

	/**
	 * Konstante, bis zu welchem Grad das Pattern gebaut werden soll
	 */
	private static final int ITERATIONS = 8;

	/**
	 * Main-Methode zum Starten des Programms
	 * 
	 * @param args
	 * @throws ClassNotFoundException
	 * @throws InstantiationException
	 * @throws IllegalAccessException
	 * @throws UnsupportedLookAndFeelException
	 */
	public static void main(String args[]) throws ClassNotFoundException,
			InstantiationException, IllegalAccessException,
			UnsupportedLookAndFeelException {

		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

		ChristmasTreePattern ctp = new ChristmasTreePattern();
		ChristmasFrame cf = new ChristmasFrame(ctp, ITERATIONS);
		cf.buildFrame();

	}

}
