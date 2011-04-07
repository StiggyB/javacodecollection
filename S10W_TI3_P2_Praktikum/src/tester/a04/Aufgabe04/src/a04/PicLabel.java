package tester.a04.Aufgabe04.src.a04;

/**
 * 
 * @author David Niederwestberg, Marcel Ehrlitzer
 *
 */
import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JLabel;

public class PicLabel extends JLabel {

	private static final long serialVersionUID = 1L;
	private int x;
	private int y;
	private int xIncrement;
	private int yIncrement;
	private int xBound;
	private int yBound;

	public PicLabel(int x, int y, int xIncrement, int yIncrement, File f) {
		this.x = x;
		this.y = y;
		this.xIncrement = xIncrement;
		this.yIncrement = yIncrement;
		ImageIcon i = new ImageIcon(f.getAbsolutePath());
		this.xBound = i.getIconWidth();
		this.yBound = i.getIconHeight();
		this.setBounds(this.x, this.y, this.xBound, this.yBound);
		this.setIcon(i);
	}

	public void move() {
		if (((this.x > 800 - this.xBound) || (this.x < 1))) {
			this.xIncrement = this.xIncrement * -1;
			// System.out.println("x * -1");
		} else if (((this.y > 600 - this.yBound - 25) || (this.y < 1))) {
			this.yIncrement = this.yIncrement * -1;
			// System.out.println("y * -1");
		}
		this.x += this.xIncrement;
		this.y += this.yIncrement;
		this.setBounds(x, y, this.xBound, yBound);

	}

	public int getX() {
		return this.x;
	}

	public int getY() {
		return this.y;
	}

	public void swapDirectionY() {
		this.yIncrement = this.yIncrement * -1;
	}

	public void swapDirectionX() {
		this.xIncrement = this.xIncrement * -1;
	}
}
