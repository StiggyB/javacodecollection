package tester.a02;

import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JLabel;

public class TestFrameErrorFrame {

	public TestFrameErrorFrame() {
	JFrame errorFrame = new JFrame();
	JLabel errorLabel = new JLabel("Minimum one entry is false or not complete.", JLabel.CENTER);
	errorFrame.add(errorLabel);
	errorFrame.setVisible(true);
	errorFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	errorFrame.setSize(new Dimension(500, 250));
//	errorFrame.pack();
	}
	
	public static void main(String[] args) {
		new TestFrameErrorFrame();
	}
}
