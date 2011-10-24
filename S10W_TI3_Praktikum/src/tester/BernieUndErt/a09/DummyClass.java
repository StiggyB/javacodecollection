package tester.BernieUndErt.a09;

import java.io.Serializable;
import javax.management.DescriptorKey;
import javax.swing.JTree;

/**
 * Dies ist eine recht "nutzlose" Klasse, sie dient uns nur zu Testzwecken bei
 * der "Objektschnueffelei"
 * 
 * @author Bernie und Ert
 * @version 0.1beta
 */
@MyAnnotation(name = "DummyAnnotation", value = "Tach, Post!")
class DummyClass extends JTree implements Serializable, Cloneable, IDummyClass {

	private static final long serialVersionUID = 1L;

	private Integer privateInteger;
	public Integer publicInteger;

	/**
	 * Defaultkonstruktor f�r die DummyClass
	 */
	public DummyClass() {
		this(1, 2);
	}

	// private DummyClass(int a) {
	// this(1, 2);
	// }

	/**
	 * Parametrisierter Konstruktor 
	 * @param i Wert f�r privateInteger
	 * @param j Wert f�r publicInteger
	 */
	public DummyClass(int i, int j) {
		privateInteger = i;
		publicInteger = j;
	}

	/**
	 * Liefert Wert von privateInteger
	 * @return int
	 */
	@Override
	public Integer getPrivateInteger() {
		return privateInteger;
	}

	/**
	 * Setzt privateInteger auf den �bergebenen Wert
	 * @param privateInteger
	 */
	@Override
	public void setPrivateInteger(Integer privateInteger) {
		this.privateInteger = privateInteger;		
	}

	/**
	 * Liefert Wert von publicInteger
	 * @return publicInteger
	 */
	@Override
	@DescriptorKey(value = "1337")
	@Deprecated
	public Integer getPublicInteger() {
		return publicInteger;
	}

	/**
	 * Setzt den Wert von publicInteger
	 * @param publicInteger
	 */
	@Override
	@Deprecated
	public void setPublicInteger(Integer publicInteger) {
		this.publicInteger = publicInteger;		
	}

}
