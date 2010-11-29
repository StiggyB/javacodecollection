package a04;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 04<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, PR2 Praktikum
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


public class IconModel {
	
	private List<IconLabel> labelList = new ArrayList<IconLabel>();

	public List<IconLabel> getLabelList() {
		return labelList;
	}

	public void setLabelList(List<IconLabel> labelList) {
		this.labelList = labelList;
	}

	/**
	 * @throws IOException
	 */
	public void init() throws IOException {
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
		labelList.add(new IconLabel(300, 10, 3, 2, file));
		labelList.add(new IconLabel(100, 200, -2, 1, file));
		labelList.add(new IconLabel(150, 50, 10, 10, file));

	}
	
	public void run(IconView view) {
		for(;;) {
			for(IconLabel labelX : labelList) {
				labelX.move(view);
				labelX.repaint();
				for(IconLabel labelY : labelList) {
					navigateIcons(labelX, labelY, view);
				}
			}
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	private void navigateIcons(IconLabel labelX, IconLabel labelY, IconView view) {
		if ((labelX != labelY) && (labelX.getBounds().intersects(labelY.getBounds()))) {
			Rectangle rect = labelX.getBounds().intersection(labelY.getBounds());
			if (rect.height < rect.width) {
				labelX.swapVektorX();
				labelY.swapVektorX();
			} else if (rect.height > rect.width) {
				labelX.swapVektorY();
				labelY.swapVektorY();
			} else {
				labelX.swapVektorX();
				labelX.swapVektorY();
				labelY.swapVektorX();
				labelY.swapVektorY();
			}
			labelX.move(view);
		}
	}
}
