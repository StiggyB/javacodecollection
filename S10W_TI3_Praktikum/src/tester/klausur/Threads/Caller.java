package tester.klausur.Threads;

import java.util.concurrent.Callable;

public class Caller extends Object implements Callable<Long> {	
	@Override
	public Long call() throws Exception {
		while(true) {
			long t = System.currentTimeMillis();
			for (int i = 0; i < 1000; i++) {
				System.out.println("I´m calling!");
			}
			return (System.currentTimeMillis() - t );
		}
	}
}