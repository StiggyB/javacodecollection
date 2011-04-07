package a00_KHB;

import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
/**
 * @author Sven Eric Panitz
 * @author Bernd Kahlbrandt Einige sinnvolle Erweiterungen eingef�gt.
 *
 */
public class ShowInFrame{
	public static void show(JComponent c){
	show("",c);
	}
/**
 * Passt das L&F auf das jeweilige Satem an und zeigt das Element dann in einem JFrame an.&nbsp;
 * Beim Schlie�en des Frames wird die Anwendung beendet.
 * 
 * @param title Der Titel der Anwednung, der in der Caption des Frames angezeigt wird.
 * @param c Die darzustellende Komponente.
 */
	public static void show(String title, JComponent c){
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException e1) {
			e1.printStackTrace();
		} catch (InstantiationException e1) {
			e1.printStackTrace();
		} catch (IllegalAccessException e1) {
			e1.printStackTrace();
		} catch (UnsupportedLookAndFeelException e1) {
			e1.printStackTrace();
		}
		JFrame f = new JFrame(title);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.add(c);
		f.pack();
		f.setVisible(true);
	}
}
