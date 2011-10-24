package a08;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 08<br>
 * 
 * Version: V0<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, PR2 Praktikum
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

import java.io.Serializable;

import javax.swing.JTree;

import org.junit.Test;

import a08.TestAnno;

/**
 * This class is a test class to search through it.
 *
 */
@SuppressWarnings("all")
@TestAnno(exception = RuntimeException.class)
public class Clazz extends JTree implements Serializable{

	private class Memeber{
		
	}
	
	interface I1 {
		
	}
	
	public int value;
	public double dvalue;
	private int integer;
	String str = "123";
	Object obj;
	
	//default Constructor
	public Clazz() {
	}
	
	public Clazz(int value){
		this.value = value;
		this.integer = value;
	}
	
	public int getValue() {
		return this.value;
	}
	
	public void setValue(int value, String s) {
		this.value = value;
	}

//	@Override
//	@Deprecated
//	@Test
//	public String toString() {
//		return this.getClass().getCanonicalName();
//	}
	
}
