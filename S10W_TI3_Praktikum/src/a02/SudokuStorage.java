package a02;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 02<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

import javax.swing.JFileChooser;

/**
 * This class contain a method to 
 * save the elements of an array in a file.
 * 
 * @author Administrator
 *
 */
public class SudokuStorage {

	public static void saveData(int[][] values) {
		int rc = JFileChooser.ERROR_OPTION;
		JFileChooser jfc = new JFileChooser();
		jfc.setFileSelectionMode(JFileChooser.FILES_ONLY);
		jfc.setSelectedFile(new File("sudokuData.txt"));
		rc = jfc.showSaveDialog(null);
		if (rc == JFileChooser.APPROVE_OPTION) {
			System.out.println(jfc.getSelectedFile().getName() + " created.");
			try {
				PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(
						new FileOutputStream(jfc.getSelectedFile()))));
				for (int[] e : values) {
					for (int i : e) {
						pw.print(i);
						pw.print("  ");
					}
					pw.println();
				}
				pw.flush();
				pw.close();
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}
	}
}
