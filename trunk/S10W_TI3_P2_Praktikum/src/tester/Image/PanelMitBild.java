package tester.Image;
 
import java.awt.*;
import javax.swing.*;
 
public class PanelMitBild { 
    public PanelMitBild () {
        JFrame f = new JFrame();
        f.setLayout(new FlowLayout());
        
        MyPanel panel = new MyPanel(Toolkit.getDefaultToolkit().getImage("background.jpeg"));
            panel.add(new JButton("Huhu"));
        f.setContentPane(panel);
        
        f.setSize(800, 600);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setVisible(true);
    }
    
    public static void main (String [] args) {
        new PanelMitBild();
    }
    
    @SuppressWarnings("serial")
    class MyPanel extends JPanel {
 
        private Image image;
 
        MyPanel(Image image) {
            if(image == null){
                System.out.println("Fehler in init!");
            }
            this.image = image;
            repaint();
        }
        
        public void paintComponent(Graphics g) {
            g.drawImage(image, 0, 0, null);
        }
    }
}