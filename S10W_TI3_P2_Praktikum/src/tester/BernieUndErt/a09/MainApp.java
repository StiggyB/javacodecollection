package tester.BernieUndErt.a09;

import java.io.IOException;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 * Klasse, welche unseren ObjectExplorer startet und das Look&Feel des Systems
 * setzt f�r das GUI.
 * 
 * @author Bernie und Ert
 * @version 1.0
 */
public class MainApp {

	/**
	 * main-Methode zum Starten des Objektbrowsers
	 * 
	 * @param args
	 *            �bergabeparameter an das Programm
	 * @throws ClassNotFoundException
	 * @throws InstantiationException
	 * @throws IllegalAccessException
	 * @throws UnsupportedLookAndFeelException
	 * @throws IOException
	 */
	public static void main(String args[]) throws ClassNotFoundException,
			InstantiationException, IllegalAccessException,
			UnsupportedLookAndFeelException, IOException {

		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

		ExplorerTree ept = new ExplorerTree();

		ept.buildFrame();

	}

}