package tester.a04;

import java.awt.Dimension;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Image;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Window;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JRootPane;


public class TestFrameImagePanel extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JLabel imageLabel;
	private JLabel iconLabel;
	
	public TestFrameImagePanel() {
		createImageIcon();
	}
	
	/**
	 * Reference: http://download.oracle.com/javase/tutorial/uiswing/components/icon.html
	 * 
	 * @param path
	 * @param description
	 * @return ImageIcon
	 */
    protected ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = getClass().getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
        }
    }
    /**
     * not functional
     * 
     * @param iconLabel
     * @param point
     */
    public void showIcon(JLabel iconLabel, Point point) {
    	point = GraphicsEnvironment.getLocalGraphicsEnvironment().getCenterPoint();
    	GraphicsDevice sd = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice();
    	sd.getClass();
    	JRootPane rootpane = new JRootPane();
    	
    	rootpane.getContentPane().add(iconLabel);
    	iconLabel.setVisible(true);
    	iconLabel.setLocation(point);
    	
    }
    
    public void moveIcon(JFrame frame) {
		Rectangle re = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds(); //Get the Screen Size!!!

    	for (int x = 0; x <= re.width; x+=126) {
    		for (int y = 0; y <= re.height; y+=60) {
    			try {
					Thread.sleep(500);					
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				Window.getWindows();
				System.out.println(re.height + ", " + re.width);
    			frame.setLocation(new Point(x, y));
    		}
    	}
    }
	
    public Point move() {
    	return new Point(0,0);
    }
    
    public void showIconsInFrame(JLabel iconLabel, Image iIcon) {
    	JFrame frame = new JFrame();
    	frame.setUndecorated(true);
    	frame.setVisible(true);
//    	frame.setLocation(new Point(0,0));
    	frame.setLocationRelativeTo(null);
    	Rectangle rect = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
    	System.out.println(rect.width + ", " + rect.height);
    	frame.setPreferredSize(new Dimension(rect.width, rect.height));
    	frame.setResizable(false);
//    	frame.setAlwaysOnTop(true);
    	frame.setLayout(null);
    	frame.getContentPane().add(iconLabel);
//    	frame.setIconImage(iIcon);
    	frame.pack();
    	iconLabel.setLocation(new Point(0, 0));
//    	moveLinear(frame, iconLabel);
    }
        
    public void moveLinear(JFrame frame, JLabel iconLabel) {
    	Rectangle rect = frame.getBounds();
    	Rectangle rect2 = iconLabel.getVisibleRect();
    	System.out.println(rect2.height);
    	for (int x = 0; x <= rect.width; x++) {
    		for (int y = 0; y <= rect.height; y++) {
    			try {
					Thread.sleep(50);					
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				System.out.println(iconLabel.getWidth() + ", " + iconLabel.getHeight());
				System.out.println(rect.height + ", " + rect.width);
				iconLabel.setLocation(new Point(x, y));
				System.out.println(x + ", " + y);
//				iconLabel.setLocation(new Point(-1600, -800));
    		}
    	}
    }
    
	public void createImageIcon() {
		java.net.URL imgURL = getClass().getResource("images/img_Rechteck_schwarz.gif");
		ImageIcon iIcon = new ImageIcon(imgURL);
		ImageIcon iIcon2 = new ImageIcon("images/img_Rechteck_schwarz.gif");
		ImageIcon image = createImageIcon("images/img_Rechteck_schwarz.gif");
		imageLabel = new JLabel(image, JLabel.CENTER);
		iconLabel = new JLabel(iIcon, JLabel.CENTER);
//		this.setIcon(iIcon2);
		System.out.println(iIcon2.getDescription());
		System.out.println(iIcon.getIconHeight() + ", " + iIcon.getIconWidth());
		
		iconLabel.setPreferredSize(new Dimension(iIcon.getIconWidth(), iIcon.getIconHeight()));
		System.out.println(iconLabel.getWidth());
//		moveIcon(frame);
		showIconsInFrame(iconLabel, iIcon.getImage());
		showIcon(imageLabel, new Point(0, 0));
		
	}
	
	public static void main(String[] args) {
		new TestFrameImagePanel();
//		ShowInFrame.show("createImageIcon", new TestFrameImagePanel());


	}
}
