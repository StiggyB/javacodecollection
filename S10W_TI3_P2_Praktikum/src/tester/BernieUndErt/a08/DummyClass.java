package tester.BernieUndErt.a08;

/**
 * 
 * @author Bernie und Ert
 * 
 *         Dies ist eine recht "nutzlose" Klasse, sie dient uns nur
 *         zu Testzwecken bei der "Objektschnueffelei"
 * 
 */

import java.io.Serializable;

import javax.swing.JTree;

class DummyClass extends JTree implements Serializable, Cloneable {

	private static final long serialVersionUID = 1L;
	
	private Integer privateInteger;
	public Integer publicInteger;
	
	public DummyClass() {
		this(1, 2);
	}
	
//	private DummyClass(int a) {
//		this(1, 2);
//	}

	public DummyClass(int i, int j) {
		privateInteger = i;
		publicInteger = j;
	}
	
	public Integer getPrivateInteger() {
		return privateInteger;
	}
	
	public void setPrivateInteger(Integer privateInteger) {
		this.privateInteger = privateInteger;
	}
	
	public Integer getPublicInteger() {
		return publicInteger;
	}
	
	public void setPublicInteger(Integer publicInteger) {
		this.publicInteger = publicInteger;
	}
	
	
	
}
