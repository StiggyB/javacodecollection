package a04;

import java.io.File;

public class MainApp {

	public static void main(String[] args) {
		ShowInFrame.showIcons(new IconLabel(50, 150, -1, 2, new File("test")/*file*/));
	}
}
