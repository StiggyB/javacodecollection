package tester;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;

public class VisibleProblem extends JFrame {

	private static final long serialVersionUID = 1L;

	private String[] columnNames = new String[] { "Column 1", "Column 2",
			"Column 3", "Column 4", "Column 5", "Column 6" };

	private Object[][] data = new Object[][] {
			new Object[] { "1-1", "1-2", "1-3", "1-4", "1-5", "1-6" },
			new Object[] { "2-1", "2-2", "2-3", "2-4", "2-5", "1-6" } };

	private double[] widthPercentages = new double[] { 0.10, 0.10, 0.10, 0.10,
			0.10, 0.50 };

	public VisibleProblem() {
		JPanel mainpane = new JPanel();
		DefaultTableModel model = new DefaultTableModel(data, columnNames);
		final JTable table = new JTable(model);
		JScrollPane scrollPane = new JScrollPane(table);

		mainpane.setLayout(new BorderLayout());
		mainpane.add(scrollPane, BorderLayout.CENTER);

		getContentPane().add(mainpane);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();

		setVisible(true);

		setExtendedState(MAXIMIZED_BOTH);

		this.addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(ComponentEvent e) {
				setPreferredColumnWidths(table, widthPercentages);
			}
		});

		setPreferredColumnWidths(table, widthPercentages);

	}

	public void setPreferredColumnWidths(JTable table, double[] widthPercentages) {
		Dimension tableDim = table.getSize();

		double total = 0;
		for (int i = 0; i < table.getColumnModel().getColumnCount(); i++) {
			total += widthPercentages[i];
		}

		for (int i = 0; i < table.getColumnModel().getColumnCount(); i++) {
			TableColumn column = table.getColumnModel().getColumn(i);
			column.setPreferredWidth((int) (tableDim.width * (widthPercentages[i] / total)));
		}
	}

	public static void main(String[] args) {
		new VisibleProblem();
	}

}

