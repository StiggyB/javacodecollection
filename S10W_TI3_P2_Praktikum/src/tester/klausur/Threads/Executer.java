package tester.klausur.Threads;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class Executer {

	public static void main(String[] args) throws InterruptedException, ExecutionException {
		
		ThreadPoolExecutor tpe = new ThreadPoolExecutor(0, 10, 0, TimeUnit.MILLISECONDS,
				new ArrayBlockingQueue<Runnable>(10));
		List<Future<?>> fList = new ArrayList<Future<?>>();
		ThreadPoolExecutor exe = (ThreadPoolExecutor) Executors.newFixedThreadPool(10);
		
		for(int i = 0; i < 5; i++) {
			System.out.println("Working");			
			fList.add( tpe.submit(new Runner()));
			fList.add(exe.submit(new Caller()));
		}		
		for (Future<?> future : fList) {
			System.out.println(future.get()); //prints the return value from call()
			exe.remove((Runnable)future);	
		}	
		exe.shutdown();
	}	
}
