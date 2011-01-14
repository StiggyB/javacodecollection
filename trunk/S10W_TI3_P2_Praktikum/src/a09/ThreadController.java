package a09;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 09<br>
 * 
 * Version: V0.1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, PR2 Praktikum
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;

/**
 * This class is a utility to
 * control and observe threads.
 *
 */
public class ThreadController {

	/**
	 * source: http://nadeausoftware.com/articles/2008/04/java_tip_how_list_and_find_threads_and_thread_groups
	 * 
	 * @return
	 */
	static Thread[] getAllThreads( ) {
	    final ThreadGroup root = getRootThreadGroup( );
	    final ThreadMXBean thbean = ManagementFactory.getThreadMXBean( );
	    int nAlloc = thbean.getThreadCount( );
	    int n = 0;
	    Thread[] threads;
	    do {
	        nAlloc *= 2;
	        threads = new Thread[ nAlloc ];
	        n = root.enumerate( threads, true );
	    } while ( n == nAlloc );
	    return java.util.Arrays.copyOf( threads, n );
	}
	

	 
	/**
	 * source: http://nadeausoftware.com/articles/2008/04/java_tip_how_list_and_find_threads_and_thread_groups
	 * 
	 * @return
	 */
	static ThreadGroup getRootThreadGroup( ) {
		ThreadGroup rootThreadGroup = null;
	    if ( rootThreadGroup != null )
	        return rootThreadGroup;
	    ThreadGroup tg = Thread.currentThread( ).getThreadGroup( );
	    ThreadGroup ptg;
	    while ( (ptg = tg.getParent( )) != null )
	        tg = ptg;
	    return tg;
	}
	
	/**
	 * @param threads
	 */
	static void printAllThreads(Thread[] threads) {
		for(Thread thr : threads) {
			System.out.println(thr);
		}
	}
}

