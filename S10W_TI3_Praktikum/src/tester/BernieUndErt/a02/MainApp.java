package tester.BernieUndErt.a02;

/**
 * 
 * @author Bernie und Ert
 * 
 *         Klasse, welche unsere Sudokuoberfl�che startet und das Look&Feel des Systems setzt
 *         f�r das GUI. Ein Objekt der Klasse SudokuIO wird vorab erzeugt und an bei der Erzeugung
 *         des SudokuFrame Objekts an dessen Konstruktor mit �bergeben. So kann damit gearbeitet 
 *         werden und es gibt weniger Querverweise und Abh�ngigkeiten.
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

		SudokuIO sudokuIO = new SudokuIO();
		SudokuFrame sudokoframe = new SudokuFrame(sudokuIO);
		sudokoframe.buildFrame();

	}

}