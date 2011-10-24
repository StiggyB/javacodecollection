package a00_KHB;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * Beispiel f�r eine L�sung, wie ich Sie f�r die ersten Aufgaben des WS 2010/11
 * erwarte. Mit diesem Ansatz k�nnen Sie die Eigenschaften der einzelnen
 * Swing-Komponenten isoliert erproben. Es gibt aber auch viele andere gute M�glichkeiten!
 * 
 * @author Bernd Kahlbrandt
 * 
 */
@SuppressWarnings("serial")
public class CounterView extends JPanel {
	JTextField countDisplay;
	JButton increment;
	JButton decrement;
	JButton reset;
	Counter counter;
/**
 * Diese Klasse besteht nur aus dem Konstruktor. Hier werden die Elemente gesetzt und
 * ActionsListener als Objekte anonymer Klassen hinzugef�gt.
 * @param resetValue Start- und ResetValue.
 */
	public CounterView(int resetValue) {
		super(new BorderLayout());
		this.counter = new Counter();
		this.countDisplay = new JTextField(Integer.toString(counter.show()));
		this.increment = new JButton("+");
		this.increment.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				counter.increment();
				countDisplay.setText(Integer.toString(counter.show()));
			}
		});
		this.decrement = new JButton("-");
		this.decrement.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				counter.decrement();
				countDisplay.setText(Integer.toString(counter.show()));
			}
		});
		this.reset = new JButton("reset");
		this.reset.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				counter.reset();
				countDisplay.setText(Integer.toString(counter.show()));
			}
		});
		this.add(this.countDisplay, BorderLayout.NORTH);
		this.add(this.reset, BorderLayout.WEST);
		this.add(this.increment, BorderLayout.CENTER);
		this.add(this.decrement, BorderLayout.EAST);
	}

	/**
	 * @param args
	 *            - keine
	 */
	public static void main(String[] args) {
		ShowInFrame.show("The Counter",new CounterView(0));
	}

}
