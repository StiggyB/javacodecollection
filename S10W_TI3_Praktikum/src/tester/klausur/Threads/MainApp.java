package tester.klausur.Threads;

public class MainApp {

	public static void main(String[] args) {
		
		Runner run = new Runner();
		run.t.start();
		
		Thread.getAllStackTraces();
		System.out.println(run.t.isAlive());
	}
}
