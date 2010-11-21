package tester.a04.Aufgabe04.src.a04;

/**
 * 
 * @author David Niederwestberg, Marcel Ehrlitzer
 *
 */
import java.awt.Rectangle;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.filechooser.FileNameExtensionFilter;

public class GUI {

	JFrame mainframe = new JFrame();
//	PicLabel pLabel1;
	List<PicLabel> list = new ArrayList<PicLabel>();
	File file = new File("./blub.gif");

	public void init() {
		this.mainframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.mainframe.setLayout(null);
		this.mainframe.setBounds(0, 0, 800, 600);
		this.mainframe.setResizable(false);
		this.mainframe.setTitle("Springende Bilder EXTRME");

		JFileChooser chooser = new JFileChooser();
		FileNameExtensionFilter filter = new FileNameExtensionFilter(
				"JPG & GIF Images", "jpg", "gif");
		chooser.setFileFilter(filter);
		int returnVal = chooser.showOpenDialog(null);
		if (returnVal == JFileChooser.APPROVE_OPTION) {
			file = chooser.getSelectedFile();
		}

		this.list.add(new PicLabel(50, 150, -1, 2, file));
		this.list.add(new PicLabel(100, 10, 3, 2, file));
		this.list.add(new PicLabel(250, 150, 2, 1, file));
		this.list.add(new PicLabel(200, 10, 1, 2, file));
		this.list.add(new PicLabel(250, 50, 1, 1, file));
		this.list.add(new PicLabel(300, 10, -3, 3, file));
		this.list.add(new PicLabel(250, 250, 2, 1, file));
		this.list.add(new PicLabel(400, 10, 3, -2, file));
		this.list.add(new PicLabel(250, 450, 10, 10, file));
		

		for (PicLabel label : this.list) {
			this.mainframe.add(label);
		}

		this.mainframe.setLocationRelativeTo(null);
		this.mainframe.setVisible(true);
		run();
	}

	public void run() {
		while (true) {
			for (PicLabel label : this.list) {
				label.move();
				label.repaint();
				for (PicLabel lab : this.list) {
					if ((label != lab)
							&& (label.getBounds().intersects(lab.getBounds()))) {
						Rectangle rec = label.getBounds().intersection(
								lab.getBounds());
						if (rec.height < rec.width) {
							lab.swapDirectionY();
							label.swapDirectionY();
						} else if (rec.height > rec.width) {
							lab.swapDirectionX();
							label.swapDirectionX();
						} else {
							lab.swapDirectionX();
							label.swapDirectionX();
							lab.swapDirectionY();
							label.swapDirectionY();
						}
						label.move();
						 System.out.println(label.getBounds().intersects(rec.getBounds()));

					}

				}
			}

			this.mainframe.repaint();

			try {
				Thread.sleep(20);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
