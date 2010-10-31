package tester;

import java.awt.BorderLayout;

import javax.swing.JFrame;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import javax.swing.table.TableRowSorter;

public class TestFrameJTableRowSorter2 extends JFrame{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	TestFrameJTableRowSorter2() {
		super("TestTable");
		String[] columns = {"ID", "Name", "Beschreibung"};
		String[][] data = {{"","",""}, {"4","5","6"}};
		
//		SudokuModel sm = new SudokuModel();
//		JTable mTable = new JTable(sm);
//		TableRowSorter<TableModel> mSort = new TableRowSorter<TableModel> (sm);
//		mTable.setRowSorter(mSort);
		
		DefaultTableModel dm = new DefaultTableModel(data, columns);
		JTable table = new JTable(dm);
		//Standart Implementierung eines RowSorter
		TableRowSorter<DefaultTableModel> sort = new TableRowSorter<DefaultTableModel> (dm);
		JTableHeader th = table.getTableHeader();
		
		
		table.setRowSorter(sort);
		this.add(th, BorderLayout.NORTH);
		this.add(table, BorderLayout.CENTER);
		this.setSize(320, 133);
		this.pack();
	}
	
	public static void main (String[] args ) {
		TestFrameJTableRowSorter2 testTable = new TestFrameJTableRowSorter2();
		testTable.setVisible(true);		
	}
}
