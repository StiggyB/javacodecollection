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

import java.io.Serializable;
import java.lang.annotation.Annotation;

import javax.management.DescriptorKey;
import javax.swing.JTree;

import org.junit.Test;

import a08.TestAnno;

/**
 * This class is a test class to search through it.
 *
 */
@SuppressWarnings("all")
@TestAnno(exception = RuntimeException.class)
public class Clazz extends JTree implements Serializable, TestAnno {

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

	@Override
	public Class<? extends Exception> exception() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	@DescriptorKey(value = "1")
	@Deprecated
	public double id() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public String value() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Class<? extends Annotation> annotationType() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	@Deprecated
	@Test
	public String toString() {
		return this.getClass().getCanonicalName();
	}
	
}
