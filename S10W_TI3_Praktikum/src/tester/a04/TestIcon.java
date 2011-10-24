package tester.a04;

import java.awt.Container;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JLabel;

public class TestIcon {

	
	private static void create() {
		ImageIcon iIcon = new ImageIcon("images/img_Rechteck_schwarz.gif");
		JLabel iconLabel = new JLabel(iIcon, JLabel.CENTER);
		TestIcon tIcon = new TestIcon();
		tIcon.build(iconLabel.getRootPane());
	}
	
	private void build(Container cont) {
		cont.setLayout(new BoxLayout(cont, BoxLayout.PAGE_AXIS));
		JComponent tComp = new TestComponent(this);
		cont.add(tComp);
	}
	
	public static void main(String[] args) {
		create();
	}
}
