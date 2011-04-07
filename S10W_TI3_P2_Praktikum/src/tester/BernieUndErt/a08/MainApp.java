package tester.BernieUndErt.a08;

/**
 * 
 * @author Bernie und Ert
 * 
 *         Klasse, welche unseren ObjectExplorer startet und das Look&Feel des Systems setzt
 *         f�r das GUI. 
 * 
 */

import java.io.IOException;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class MainApp {

	public static void main(String args[]) throws ClassNotFoundException,
			InstantiationException, IllegalAccessException,
			UnsupportedLookAndFeelException, IOException {

		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

		ExplorerTree ept = new ExplorerTree();
		
		ept.buildFrame();
		
	}

}