package tester;

import java.text.NumberFormat;
import java.util.Locale;

import javax.swing.table.DefaultTableCellRenderer;


public class SudokuEditor extends DefaultTableCellRenderer {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private NumberFormat formatter;
	
	public void setValue(Object value) {
		
        if (formatter==null) {
            formatter = NumberFormat.getIntegerInstance(Locale.GERMAN);
        }
        setText((value == null) ? "" : formatter.format(value));
    }
	

}
