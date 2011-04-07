package tester.BernieUndErt.a02;

/**
 * 
 * @author Bernie und Ert
 * 
 *         Klasse, die unseren Swing-Frame f�r den BMI Rechner erzeugt.
 *         Die einzige Logikmethode calcBmi() haben wir nicht extra in eine einzelne Klasse
 *         ausgelagert. Man h�tte jedoch alles in die drei Klassen BMIStart, BMICalc und BMIFrame 
 *         teilen k�nnen :)
 * 
 */

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import javax.swing.JFileChooser;
import javax.swing.table.TableModel;

public class SudokuIO {

	public void saveSudoku(SudokuTable[][] tables) throws IOException {

		JFileChooser fc = new JFileChooser();
		fc.setDialogTitle("Sudoku speichern...");

		if (fc.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
			ObjectOutputStream os = new ObjectOutputStream(
					new FileOutputStream(fc.getSelectedFile()));

			TableModel models[][] = new TableModel[3][3];
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					models[i][j] = tables[i][j].getModel();
				}
			}

			os.writeObject(models);
			os.flush();
			os.close();
		}

	}

	public TableModel[][] loadSudoku() throws IOException,
			ClassNotFoundException {

		JFileChooser fc = new JFileChooser();
		TableModel[][] models = null;
		fc.setDialogTitle("Sudoku laden...");

		int returnVal = fc.showOpenDialog(fc);
		if (returnVal == JFileChooser.APPROVE_OPTION) {
			ObjectInputStream ois = new ObjectInputStream(new FileInputStream(
					fc.getSelectedFile()));
			models = (TableModel[][]) ois.readObject();
			ois.close();
		}

		return models;

	}

}