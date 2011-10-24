package tester.BernieUndErt.a02;

/**
 * 
 * @author Bernie und Ert
 * 
 *         Klasse die JTable erweitert. Die Methode isCellEditable musste 
 *         �berschrieben werden. Mit der eigenen Methode setRandomVaueAt
 *         wird der Wert in der Zelle gesetzt und anschlie�end im 
 *         Bool-Array das entsprechende K�stchen auf true gesetzt.
 *         Wird nun die Methode isCellEditable gecallt, gibt diese
 *         das Gegenteil des Inhalts aus der entsprechenden Bool-Array-Stelle
 *         aus. Ist ein Feld mit einem random-Wert belegt, erh�lt es den Wert
 *         true, wird gefragt, ob es editierbar ist, sagt die Methode folglich
 *         !true, also false. Diese Version ist k�rzer als ein l�ngerer tern�rer
 *         Operator, w�re aber genausom�glich und beim ersten Hinsehen vlt
 *         einfacher zu verstehen. 
 *        
 * 
 */

import java.io.Serializable;

import javax.swing.JTable;

class SudokuTable extends JTable implements Serializable {

	private static final long serialVersionUID = 1L;
	boolean randomSetFields[][] = new boolean[3][3];

	public SudokuTable(int numRows, int numColumns) {
		super(numRows, numColumns);
	}

	@Override
	public boolean isCellEditable(int row, int column) {
		return !randomSetFields[row][column];
	}

	public void setRandomValueAt(int randomNumber, int row, int column) {
		super.setValueAt(randomNumber, row, column);
		randomSetFields[row][column] = true;
	}

}