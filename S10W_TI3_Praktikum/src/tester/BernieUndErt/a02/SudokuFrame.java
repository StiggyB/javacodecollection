package tester.BernieUndErt.a02;

/**
 * 
 * @author Bernie und Ert
 * 
 *         Klasse, die unseren Swing-Frame f�r Sudoku erzeugt.
 *         Hier bauen wir unseren Frame zusammen und werfen die neun einzelnen Tabellen
 *         dann in den Frame und in ein zweidimensionales JTable-Array.
 *         Sudoku-Logik und IO sind in eigene Klassen ausgelagert, weiterhin haben wir die
 *         Klasse SudokuTable, die JTable erweitert.
 * 
 */

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingConstants;
import javax.swing.table.TableModel;

public class SudokuFrame {

	JFrame frame = new JFrame();
	SudokuTable[][] tables = new SudokuTable[3][3];
	JButton loadButton = new JButton();
	JButton saveButton = new JButton();
	JLabel labelTitle2 = new JLabel("<html><h1>Sudoku</h1></html>");
	private SudokuIO sudokuIO;

	public SudokuFrame(SudokuIO sudokuIO) {
		this.sudokuIO = sudokuIO;
	}

	ActionListener listenerSaveLoadButton = new ActionListener() {

		@Override
		public void actionPerformed(ActionEvent event) {
			try {
				if (saveButton == event.getSource()) {
					System.out.println("SPEICHERN!");
					sudokuIO.saveSudoku(tables);
				}

				if (loadButton == event.getSource()) {
					System.out.println("LADEN!");
					// just4help();
					TableModel[][] models = sudokuIO.loadSudoku();
					System.out.println("");

					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tables[i][j].setModel(models[i][j]);
						}
					}

					// just4help();

				}

			} catch (IOException e) {
				e.printStackTrace();
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}

		}
	};

	public void buildFrame() {

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("1337 Sudoku (c) Bernie & Ert");
		frame.setLayout(new GridLayout(4, 3));

		loadButton.setText("laden");
		loadButton.addActionListener(listenerSaveLoadButton);
		frame.add(loadButton);

		labelTitle2.setHorizontalAlignment(JLabel.CENTER);
		frame.add(labelTitle2);

		saveButton.setText("speichern");
		saveButton.addActionListener(listenerSaveLoadButton);
		frame.add(saveButton);

		frame.setResizable(false);
		frame.setVisible(true);

		final SudokuLogik logik = new SudokuLogik(tables);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tables[i][j] = buildTable();
				frame.add(tables[i][j]);
			}
		}

		logik.fillTables();
		frame.pack();
	}

	private SudokuTable buildTable() {

		SudokuTable table = new SudokuTable(3, 3);
		table.setRowHeight(60);
		table.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		JLabel centerRenderer = ((JLabel) table
				.getDefaultRenderer(Object.class));
		centerRenderer.setHorizontalAlignment(SwingConstants.CENTER);
		table.setVisible(true);

		return table;
	}

	// lediglich eine Helfermethode zum Debuggen geladener Spiele
	public void just4help() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						System.out.print(tables[i][j].getValueAt(k, l) + ", ");

					}

				}

			}

		}
	}

}