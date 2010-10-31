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

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTable;
import javax.swing.SwingConstants;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumnModel;

/**
 * This View does not provide a full functional Model to play Sudoku.
 * The Solve- button activate a storage of the actual elements.
 *
 */
public class SudokuView extends JPanel implements ActionListener, TableModelListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JPanel editArea;
	private JPanel buttonArea;
	private JTable sudokuTable;
	private JLabel sudokuHeader;
	private JButton solveButton;
	private JButton clearButton;
	private SudokuModel sudokuModel;

	public SudokuView(SudokuModel sm) {
		super();
		this.sudokuModel = sm;
		createButtonArea();
		createEditArea();
		createMainArea();
	}
	
	public JTable getSudokuTable() {
		return this.sudokuTable;
	}

	private void createEditArea() {
		sudokuHeader = new JLabel("SUDOKU", JLabel.CENTER);
		sudokuHeader.setBorder(BorderFactory.createCompoundBorder(BorderFactory
				.createTitledBorder(""), BorderFactory.createEmptyBorder(5, 5,
				5, 5)));
		
		sudokuTable = new JTable(sudokuModel) {
			/**
				 * This inner class overrides the prepareRenderer
				 * to set the alignment of the cells central. 
				 */
			private static final long serialVersionUID = 1L;

			@Override
			public Component prepareRenderer(final TableCellRenderer renderer,
					final int row, final int column) {
				Component c = super.prepareRenderer(renderer, row, column);
				if (c instanceof JLabel) {
					JLabel label = (JLabel) c;
					label.setHorizontalAlignment(JLabel.CENTER);
				}
				return c;
			}
		};
		//-- Line 95 is commented because it generate a Stackoverflow
//		sudokuTable.getModel().addTableModelListener(this);
		
		sudokuTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		sudokuTable.setCellSelectionEnabled(true);
		sudokuTable.setRowHeight(40);
		TableColumnModel columnModel = sudokuTable.getColumnModel();
		for (int i = 0; i < columnModel.getColumnCount(); i++) {
			columnModel.getColumn(i).setPreferredWidth(40);
		}
		sudokuTable.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		JLabel centerRenderer = ((JLabel) sudokuTable
				.getDefaultRenderer(Object.class));
		centerRenderer.setHorizontalAlignment(SwingConstants.CENTER);
		sudokuTable.setVisible(true);
		sudokuTable.setBorder(BorderFactory.createCompoundBorder(BorderFactory
				.createTitledBorder(""), BorderFactory.createEmptyBorder(1, 1,
				1, 1)));

		editArea = new JPanel();
		editArea.setLayout(new BorderLayout(5, 5));
		editArea.add(sudokuHeader, BorderLayout.NORTH);
		editArea.add(sudokuTable, BorderLayout.CENTER);
	}

	private void createButtonArea() {
		solveButton = new JButton("Solve");
		solveButton.setToolTipText("Press this button to solve the game.");
		solveButton.setActionCommand("solve");
		solveButton.addActionListener(this);

		clearButton = new JButton("New Game");
		clearButton.setToolTipText("press this button to clear the game.");
		clearButton.setActionCommand("new");
		clearButton.addActionListener(this);

		buttonArea = new JPanel();
		buttonArea.setLayout(new GridLayout(0, 2));
		buttonArea.add(clearButton);
		buttonArea.add(solveButton);
	}

	private void createMainArea() {
		this.setBorder(BorderFactory.createCompoundBorder(BorderFactory
				.createTitledBorder(""), BorderFactory.createEmptyBorder()));
		this.setLayout(new BorderLayout(5, 5));
		this.add(editArea, BorderLayout.CENTER);
		this.add(buttonArea, BorderLayout.SOUTH);
		this.setPreferredSize(new Dimension(500, 446));
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals("solve")) {
			sudokuModel.solveGame();
		} else if (e.getActionCommand().equals("new")) {
			sudokuModel.clearGame();
		}
	}

	/**
	 * - Actually not in use (see Documentation) -
	 * Permit consistently a MVC - Architecture.
	 * 
	 * @param e the event
	 */
	@Override
	public void tableChanged(TableModelEvent e) {
		int row = e.getFirstRow();
		int column = e.getColumn();
		SudokuModel model = e.getSource() instanceof SudokuModel ? (SudokuModel)(e.getSource()) : null;
		if (model != null) {	
			model.setValueAt(sudokuTable.getValueAt(row, column), row, column);
		}
	}
}
