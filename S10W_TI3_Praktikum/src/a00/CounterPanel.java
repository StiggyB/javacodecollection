package a00;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 00<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;



public class CounterPanel extends JPanel{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private Counter counter;
	private JTextField cntDisplay;
	private JButton increment;
	private JButton decrement;
	private JButton reset;
	
	public CounterPanel(int initValue) {
		super(new GridLayout(1, 1));
		this.counter = new Counter();
		this.createButtons();
		this.cntDisplay = new JTextField(Integer.toString(counter.show()));
		this.createPanel();
		this.createFrame();
	}
	
	private void createButtons() {
		increment = new JButton("+");
		this.increment.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				counter.increment();
				cntDisplay.setText(Integer.toString(counter.show()));
						
			}
		});
		this.decrement = new JButton("-");
		this.decrement.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				counter.decrement();
				cntDisplay.setText(Integer.toString(counter.show()));
			}
		});
		reset = new JButton("reset");
		this.reset.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				counter.reset();
				cntDisplay.setText(Integer.toString(counter.show()));
				
			}
		});
	}
	
	private void createPanel() {
		this.add(cntDisplay);
		this.add(this.reset);
		this.add(this.increment);
		this.add(this.decrement);
	}
	
	private void createFrame() {
		JFrame frame = new JFrame("Counter");
		frame.add(this);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		frame.pack();
	}
	
	public static void main(String[] args) {
		new CounterPanel(0);
	}
}
