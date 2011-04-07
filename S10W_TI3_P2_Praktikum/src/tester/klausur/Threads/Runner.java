package tester.klausur.Threads;

public class Runner implements Runnable {
	Thread t;	
	public Runner() {
		this.t = new Thread(t);
		t.start();
	}	
	@Override
	public void run() {
		while(true) {
			System.out.println("I´m running!");
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
