package a01v2;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 01<br>
 * 
 * Version: V2<br>
 * Aenderungen: Reduzierung auf einen JSlider 
 * 				durch die Funktionsunterscheidung mit JRadio Buttons
 * 
 * Quellen: API, Swing
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class BmiView extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private BmiCalculator bmi;
	private JPanel editArea;
	private JPanel buttonArea;
	private JPanel mainArea;
	private JLabel weightLabel;
	private JLabel heightLabel;
	private JLabel bmiLabel;
	private JSlider weightSlider;
	private JSlider heightSlider;
	private JTextField weightField;
	private JTextField heightField;
	private JTextField bmiField;
	private JButton calculate;

	public BmiView() {
		createEditArea();
		createSliderArea();
		createButtonArea();
		createMainArea();
		this.add(mainArea, BorderLayout.EAST);
		bmi = new BmiCalculator();
	}

	private void createSliderArea() {
		weightSlider = new JSlider(JSlider.HORIZONTAL, 25, 200, 68);
		weightSlider.setMajorTickSpacing(25);
		weightSlider.setMinorTickSpacing(5);
		weightSlider.setPaintLabels(true);
		weightSlider.setPaintTicks(true);
		weightSlider.addChangeListener(
		/**
		 * @author Administrator
		 * 
		 */
		new ChangeListener() {

			@Override
			public void stateChanged(ChangeEvent e) {
				JSlider source = e.getSource() instanceof JSlider ? (JSlider) e
						.getSource() : null;
				weightField.setText(Integer.toString(source.getValue()));
			}
		});

		heightSlider = new JSlider(JSlider.VERTICAL, 140, 200, 176);
		heightSlider.setMajorTickSpacing(10);
		heightSlider.setMinorTickSpacing(2);
		heightSlider.setPaintLabels(true);
		heightSlider.setPaintTicks(true);
		heightSlider.addChangeListener(
		/**
		 * @author Administrator
		 * 
		 */
		new ChangeListener() {

			@Override
			public void stateChanged(ChangeEvent e) {
				JSlider source = e.getSource() instanceof JSlider ? (JSlider) e
						.getSource() : null;
				float height = (float) source.getValue() / 100;
				heightField.setText(Float.toString(height));
			}
		});

		this.setLayout(new BorderLayout(5, 5));
		this.setBorder(BorderFactory.createCompoundBorder(BorderFactory
				.createTitledBorder(""), BorderFactory.createEmptyBorder(5, 5,
				5, 5)));
		this.add(weightSlider, BorderLayout.SOUTH);
		this.add(heightSlider, BorderLayout.WEST);
	}

	private void createEditArea() {
		weightLabel = new JLabel("Weight");
		heightLabel = new JLabel("Height");
		bmiLabel = new JLabel("BMI");
		JLabel kgLabel = new JLabel("kg");
		JLabel mLabel = new JLabel("m");
		weightField = new JTextField(); // eventuell mit Init-Wert
		heightField = new JTextField(); // eventuell mit Init-Wert
		bmiField = new JTextField();

		editArea = new JPanel(new GridLayout(0, 3, 6, 3));
		editArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory
				.createTitledBorder(""), BorderFactory.createEmptyBorder(10,
				10, 10, 10)));
		editArea.setPreferredSize(new Dimension(80, 120));
		editArea.add(weightLabel);
		editArea.add(weightField);
		editArea.add(kgLabel);
		editArea.add(heightLabel);
		editArea.add(heightField);
		editArea.add(mLabel);
		editArea.add(bmiLabel);
		editArea.add(bmiField);
	}

	private void createButtonArea() {
		calculate = new JButton("Calculate");
		calculate.addActionListener(
		/**
		 * Anonyme Klasse, die beim JButton calculate angemeldet ist mit lokaler
		 * Exceptionbehandlung - letzte Moeglichkeit zum "catch".
		 * 
		 * @author Administrator
		 * 
		 */
		new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					float weight = Float.parseFloat(weightField.getText());
					float height = Float.parseFloat(heightField.getText());
					bmi.calcBmi(weight, height);
					bmiField.setText(Float.toString(bmi.show()));
				} catch (NumberFormatException ex) {
					ex.printStackTrace();
					JOptionPane
							.showMessageDialog(
									null,
									"Error: Minimum one entry is false or not complete.",
									"Entry Error", JOptionPane.WARNING_MESSAGE);
				}
			}
		});

		buttonArea = new JPanel(new FlowLayout(FlowLayout.RIGHT));
		buttonArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory
				.createEmptyBorder(), BorderFactory.createEmptyBorder(10, 10,
				10, 10)));
		buttonArea.add(calculate);
	}

	private void createMainArea() {
		mainArea = new JPanel(new BorderLayout(0, 2));
		mainArea.add(editArea, BorderLayout.NORTH);
		mainArea.add(buttonArea, BorderLayout.CENTER);
		mainArea.setPreferredSize(new Dimension(250, 300));
	}

	public static void main(String[] args) {
		ShowInFrame.show("BMI Calculator", new BmiView());
	}
}
