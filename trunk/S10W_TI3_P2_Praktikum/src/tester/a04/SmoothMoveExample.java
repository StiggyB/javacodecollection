package tester.a04;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class SmoothMoveExample extends JPanel implements
 MouseMotionListener {
  private int X, Y;
  private Image image;
  private static JFrame frame;

public static void main(String[] args) {
    frame = new JFrame();
    frame.setSize(350, 300);
    frame.setLocationRelativeTo(null);
    frame.getContentPane().add(new SmoothMoveExample());
    frame.setVisible(true);
  }
  public SmoothMoveExample() {
//    addMouseMotionListener(this);
	moveIcon();
    setVisible(true);
  }
  
  public void moveIcon() {
	  Rectangle rect = frame.getBounds();
	  System.out.println(rect.width);
	  for(int x = 0; x <= rect.getWidth(); x++) {
		  for(int y = 0; y <= rect.getHeight(); y++) {
			  System.out.println(x + ", " + y);
			  this.setLocation(new Point(x, y));
			  try {
					Thread.sleep(50);					
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		  }
	  }
  }
  
  public void mouseMoved(MouseEvent event) {
    X = (int) event.getPoint().getX();
    Y = (int) event.getPoint().getY();
    repaint();
  }
  public void mouseDragged(MouseEvent event) {
    mouseMoved(event);
  }
  public void update(Graphics graphics) {
    paint(graphics);
  }
  public void paint(Graphics g) {
  Dimension dim = getSize();
    checkImage();
    Graphics graphics = image.getGraphics();
    graphics.setColor(getBackground());
    graphics.fillRect(0, 0, dim.width, dim.height);
  paintOffscreen(image.getGraphics());
    g.drawImage(image, 0, 0, null);
  }
  private void checkImage() {
    Dimension dim = getSize();
    if (image == null || image.getWidth(null) != dim.width
        || image.getHeight(null) != dim.height) {
      image = createImage(dim.width, dim.height);
    }
  }
  public void paintOffscreen(Graphics g) {
    int size = 150;
    g.setColor(Color.pink);
    g.fillOval(X - size  / 2, Y - size  / 2, size , size );
  }
}
