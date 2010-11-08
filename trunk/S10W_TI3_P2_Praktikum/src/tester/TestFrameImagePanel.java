package tester;

import java.awt.Dimension;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Window;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JRootPane;


public class TestFrameImagePanel extends JLabel {

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
	 * @return
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
				GraphicsDevice gd;
				GraphicsEnvironment ge;
				System.out.println(re.height + ", " + re.width);
    			frame.setLocation(new Point(x, y));
    		}
    	}
    }
	
    public Point move() {
    	return new Point(0,0);
    }
    
    public void showIconsInFrame(JLabel iconLabel) {
    	JFrame frame = new JFrame();
    	frame.add(iconLabel);
    	frame.setUndecorated(true);
    	frame.setVisible(true);
    	frame.setLocation(new Point(0,0));
    	Rectangle rect = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
    	frame.setPreferredSize(new Dimension(rect.width, rect.height));
    	frame.setResizable(false);
    	frame.pack();
    	moveLinear(frame, iconLabel);
    }
    
    public void moveLinear(JFrame frame, JLabel iconLabel) {
    	Rectangle re = frame.getBounds();
    	for (int x = 0; x <= re.width; x+=126) {
    		for (int y = 0; y <= re.height; y+=60) {
    			try {
					Thread.sleep(500);					
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				System.out.println(re.height + ", " + re.width);
				iconLabel.setLocation(new Point(x, y));
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
		this.setIcon(iIcon2);
		System.out.println(iIcon2.getDescription());
		
		JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(iconLabel);//, BorderLayout.NORTH);
//		f.add(iconLabel, BorderLayout.SOUTH);
//		f.add(this, BorderLayout.CENTER);
		frame.setUndecorated(true);
		frame.setAlwaysOnTop(true);
		frame.setResizable(false);
		
		frame.setSize(400,400);
		frame.setLocation(0,0);
		frame.setLocationRelativeTo(null);
//		frame.setVisible(true);
		frame.pack();
//		moveIcon(frame);
		showIconsInFrame(iconLabel);
		showIcon(imageLabel, new Point(0, 0));
		
	}
	
	public static void main(String[] args) {
		new TestFrameImagePanel();
//		ShowInFrame.show("createImageIcon", new TestFrameImagePanel());


	}
}
