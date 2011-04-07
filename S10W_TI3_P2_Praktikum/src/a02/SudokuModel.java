package a02;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 02<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, 
 * http://www.java-forum.org/awt-swing-swt/50594-jtable-text-zentriert-darstellen.html
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

import java.io.Serializable;

import javax.swing.event.EventListenerList;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;

/**
 * This class build the model of a Sudoku Game.
 * The check if the input is correct had not implement yet.
 * 
 * @author Administrator
 *
 */
public class SudokuModel extends DefaultTableModel implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2L;
	private int rows;
	private int columns;
	private int quadSize;
	private int[][] values;
	private boolean[][] editArr;
	private SudokuView sw;

	/**
	 * Set the count of rows and columns.
	 * Calculate the size of the quadrants in the table.
	 * 
	 * @see a02.SudokuModel.initModel
	 * @see a02.SudokuModel.fillTable 
	 * @param rows
	 * @param columns
	 */
	public SudokuModel(int rows, int columns) {
		super(rows, columns);
		this.rows = rows;
		this.columns = columns;
		if (this.rows > 0 && this.columns > 0) {
			quadSize = (int) (Math.sqrt(rows / columns * 2));
			this.sw = new SudokuView(this);
			this.initModel();
			fillTable();
		}
	}

	/**
	 * Initialize the model data structures.
	 */
	private void initModel() {
		this.values = new int[rows][columns];
		for (int row = 0; row < values.length; row++) {
			for (int column = 0; column < values[0].length; column++) {
				values[row][column] = 0;
			}
		}
		this.editArr = new boolean[this.rows][this.columns];
		for (int row = 0; row < values.length; row++) {
			for (int column = 0; column < values[0].length; column++) {
				editArr[row][column] = true;
			}
		}
	}
	
	/**
	 * Fill the table with random values between 1 and 9
	 * 
	 * @see a02.SudokuModel.generateValue
	 * @see a02.SudokuModel.generateDistance
	 */
	private void fillTable() {
		int testVal = 0;
		for (int row = 0; row < values.length; row += generateDistance()) {
			for (int column = 0; column < values[0].length; column += generateDistance()) {
				do {
					testVal = generateValue();
				} while (!isValidValue(row, column, testVal));
				values[row][column] = testVal;
				setEditable(row, column);
				setValueAt(testVal, row, column);
			}
		}
	}

	private int generateValue() {
		return (int) (Math.random() * 9 + 1);
	}

	private int generateDistance() {
		return (int) (Math.random() * 2 + 1);
	}
	
	/**
	 * Bring all checks together.
	 * 
	 * @param row
	 * @param column
	 * @param value
	 * @see a02.SudokuModel.checkLinear
	 * @see a02.SudokuModel.checkQuad
	 * @return true if the value not contain
	 */
	private boolean isValidValue(int row, int column, int value) {
		boolean valid = false;
		valid = checkLinear(row, column, value) ? checkQuad(getPosition(row),
				getPosition(column), value) ? true : false : false;
		return valid;
	}

	/**
	 * Check the vertical and horizontal 
	 * line of equal values.
	 * 
	 * @param row
	 * @param column
	 * @param value
	 * @return false if the line contains the value
	 */
	private boolean checkLinear(int row, int column, int value) {
		boolean b = true;
		for (int i = 0; i < rows; i++) {
			if (value == values[row][i]) {
				b = false;
			}
		}
		for (int i = 0; i < rows; i++) {
			if (value == values[i][column]) {
				b = false;
			}
		}
		return b;
	}
	
	/**
	 * Find the start- position.
	 * 
	 * @param pos
	 * @return the start- position in the quadrant
	 */
	private int getPosition(int pos) {
		int resu = 6;
		if (pos <= 5) {
			resu = 3;
		}
		if (pos <= 2) {
			resu = 0;
		}
		return resu;
	}

	/**
	 * Check the quadrant of the matrix.
	 * 
	 * @param startRow
	 * @param startColumn
	 * @param value
	 * @see a02.SudokuModel.getPosition
	 * @return false if the quadrant contains the value
	 */
	private boolean checkQuad(int startRow, int startColumn, int value) {
		boolean b = true;
		for (int row = startRow; row < startRow + quadSize; row++) {
			for (int column = startColumn; column < startColumn + quadSize; column++) {
				if (value == values[row][column]) {
					b = false;
				}
			}
		}
		return b;
	}

	/**
	 * Set the specific cell editable.
	 * 
	 * @param row
	 * @param column
	 */
	private void setEditable(int row, int column) {
		editArr[row][column] = false;
	}
	
	/**
	 * Get the new elements in the table.
	 */
	public void getElements() {
		for (int row = 0; row < values.length; row++) {
			for (int column = 0; column < values[0].length; column++) {
				Object value = sw.getSudokuTable().getValueAt(row, column);
				try {
					if (value != null) { 
							if (value != "") {
								values[row][column] = Integer
									.parseInt(value.toString());
							} else {
								values[row][column] = 0;
							}
					}
				} catch (NumberFormatException e) {
					System.out.println("ERROR");
					e.printStackTrace();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
		printValues();
	}
	
	/**
	 * Call saveData() to store the actual elements of the model.
	 */
	public void solveGame() {
		getElements();
		SudokuStorage.saveData(this.values);
	}
	
	/**
	 * Clear the elements of the model and table.
	 */
	public void clearGame() {	
		for (int row = 0; row < values.length; row++) {
			for (int column = 0; column < values[0].length; column++) {
				fireTableCellUpdated(row, column);
				sw.getSudokuTable().setValueAt("", row, column);
			}
		}
		this.initModel();
		fillTable();
	}
	
	/**
	 * print the elements of the model.
	 */
	private void printValues() {
		for (int row = 0; row < values.length; row++) {
			for (int column = 0; column < values[0].length; column++) {
				System.out.printf("%d  ", values[row][column]);
			}
			System.out.println();
		}
	}
	
    /**
     *  Returns true if the specific boolean value 
     *  in EditArr is true, too. Otherwise false.
     *	
     *  @param  row the row being queried
     *  @param  column the column being queried
     *  @return false or rather true
     */
	@Override
	public boolean isCellEditable(int row, int column) {
		return editArr[row][column] == false ? false : true;
	}
	
    /**
     * Forwards the given notification event to all
     * <code>TableModelListeners</code> that registered
     * themselves as listeners for this table model.
     *
     * @param e  the event to be forwarded
     *
     * @see #addTableModelListener
     * @see TableModelEvent
     * @see EventListenerList
     */
	/* (non-Javadoc)
	 * @see javax.swing.table.AbstractTableModel#fireTableChanged(javax.swing.event.TableModelEvent)
	 */
	@Override
    public void fireTableChanged(TableModelEvent e) {
		// Guaranteed to return a non-null array
		Object[] listeners = listenerList.getListenerList();
		// Process the listeners last to first, notifying
		// those that are interested in this event
		// -- I tried to prevent the Stackoverflow in line 295 but does not work
		for (int i = listeners.length-2; i>=0; i-=2) {
		    if (listeners[i]==TableModelListener.class && listeners[i] != listeners[i+1]) {
		    	((TableModelListener)listeners[i+1]).tableChanged(e);
		    }
		}
    }
	
    /**
     * Notifies all listeners that the value of the cell at 
     * <code>[row, column]</code> has been updated.
     *
     * @param row  row of cell which has been updated
     * @param column  column of cell which has been updated
     * @see TableModelEvent
     * @see EventListenerList
     */
	@Override
    public void fireTableCellUpdated(int row, int column) {
        fireTableChanged(new TableModelEvent(this, row, row, column));
    }
}
