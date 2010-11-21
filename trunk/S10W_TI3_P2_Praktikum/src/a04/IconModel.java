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

import java.awt.Rectangle;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

import tester.a04.Aufgabe04.src.a04.PicLabel;

public class IconModel {
	
	private static List<IconLabel> labelList = new ArrayList<IconLabel>();
	
	public static List<IconLabel> getList() {
		return labelList;
	}

	public static void setList(List<IconLabel> list) {
		IconModel.labelList = list;
	}

	public static void init() throws IOException {
		String defaultPath = "./a04/icons/fish.gif";
		File file = new File(defaultPath);
		
		JFileChooser jfc = new JFileChooser();
		FileNameExtensionFilter exFilter = new FileNameExtensionFilter("GIF / JPG", "gif", "jpg");
		jfc.setFileFilter(exFilter);
		int rc = jfc.showOpenDialog(null);
		if (rc == JFileChooser.APPROVE_OPTION) {
			file = jfc.getSelectedFile();
		}
		
		labelList.add(new IconLabel(250, 150, 2, 1, file));
		labelList.add(new IconLabel(50, 150, -1, 2, file));
		labelList.add(new IconLabel(100, 10, 3, 2, file));
	}
	
	public static void run() {
		while (true) {
			for (IconLabel label : labelList) {
				label.move();
				label.repaint();
				for (IconLabel lab : labelList) {
					if ((label != lab)
							&& (label.getBounds().intersects(lab.getBounds()))) {
						Rectangle rec = label.getBounds().intersection(
								lab.getBounds());
						if (rec.height < rec.width) {
							lab.swapVektorY();
							label.swapVektorY();
						} else if (rec.height > rec.width) {
							lab.swapVektorX();
							label.swapVektorX();
						} else {
							lab.swapVektorX();
							label.swapVektorX();
							lab.swapVektorY();
							label.swapVektorY();
						}
						label.move();
						 System.out.println(label.getBounds().intersects(rec.getBounds()));

					}

				}
			}

			ShowInFrame.getFrame().repaint();
			try {
				Thread.sleep(20);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static void run2() {
		for(;;) {
			for(IconLabel labelX : labelList) {
				labelX.move();
				labelX.repaint();
				for(IconLabel labelY : labelList) {
					navigateIcons(labelX, labelY);
					
				}
			}
			ShowInFrame.getFrame().repaint();
			try {
				Thread.sleep(20);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	private static void navigateIcons(IconLabel labelX, IconLabel labelY) {
		if ((labelX != labelY) && (labelX.getBounds().intersects(labelY.getBounds()))) {
			Rectangle rect = labelX.getBounds().intersection(labelY.getBounds());
			if (rect.height > rect.width) {
				labelX.swapVektorX();
				labelY.swapVektorX();
			} else if (rect.height < rect.width) {
				labelX.swapVektorY();
				labelY.swapVektorY();
			} else {
				labelX.swapVektorX();
				labelX.swapVektorY();
				labelY.swapVektorX();
				labelY.swapVektorY();
			}
			labelX.move();
			System.out.println(labelX.getBounds().intersects(rect.getBounds()));
		}
	}
	
}
