package a04;

import java.awt.Rectangle;
import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JLabel;

public class IconLabel extends JLabel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int x;
	private int y;
	private int boundX;
	private int boundY;
	private int vektorX;
	private int vektorY;
	
	public IconLabel(int x, int y, int vektorX, int vektorY, File file) {
		this.x = x;
		this.y = y;
		this.vektorX = vektorX;
		this.vektorY = vektorY;
		ImageIcon iIcon = new ImageIcon(file.getAbsolutePath());
		this.boundX = iIcon.getIconWidth();
		this.boundY = iIcon.getIconHeight();
		this.setBounds(new Rectangle(this.boundX, this.boundY));
		this.setIcon(iIcon);
	}
	
	public void move() {
		if(600/*Frame.width*/ - boundX > x) {
			swapVektorX();
		}
		if(400 - boundY > y) {
			swapVektorY();
		}
		this.x = vektorX;
		this.y = vektorY;
		this.setBounds(new Rectangle(boundX, boundY));
	}
	
	public void swapVektorX() {
		vektorX *= -1;
	}
	
	public void swapVektorY() {
		vektorY *= -1;
	}
	

}
