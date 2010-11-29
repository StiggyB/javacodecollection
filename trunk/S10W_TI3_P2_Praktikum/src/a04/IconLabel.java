package a04;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 04<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

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
		this.setBounds(this.x, this.y, this.boundX, this.boundY);
		this.setIcon(iIcon);
	}
	
	public void move(IconView view) {
		if(((x > view.getFrame().getWidth() - boundX) || (x < 1))) {
			this.swapVektorX();
		} else if(((y > view.getFrame().getHeight() - boundY) || (y < 1))) {
			this.swapVektorY();
		}
		this.x += this.vektorX;
		this.y += this.vektorY;
		this.setBounds(this.x, this.y, this.boundX, this.boundY);
	}
	
	public void swapVektorX() {
		vektorX *= -1;
	}
	
	public void swapVektorY() {
		vektorY *= -1;
	}
}
