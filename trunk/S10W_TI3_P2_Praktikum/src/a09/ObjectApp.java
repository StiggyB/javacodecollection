package a09;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 09<br>
 * 
 * Version: V0<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, PR2 Praktikum
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

/**
 * This class implements Runnable and
 * could transfer to a thread.
 *
 */
public class ObjectApp implements Runnable{

	private Object obj;
	
	public Object getObj() {
		return obj;
	}

	public void setObj(Object obj) {
		this.obj = obj;
	}

	/**
	 * This method starts the thread and 
	 * contains all executable code of this thread.
	 *  
	 * @see java.lang.Runnable#run()
	 */
	@Override
	public void run() {
//		Some Objects for testing the ObjectBrowser
		this.obj = new Clazz();

//		this.obj = new JTree();
//		this.obj = new Object();
//		this.obj = null;
		
		new ObjectView(this.obj);
		
	}

}
