package a00;
/**
 * Eine einfache Klasse zur Einführung in Java.
 * 
 * Es wird ein Wert hoch- bzw- heruntergezählt.
 * @author Bernd Kahlbrandt
 *
 */
public class Counter {
	/**
	 * Der aktuelle Wert des Counters.
	 */
	private int value;
	/**
	 * Der Anfangswert des Counters, auf den er bei Bedarf zurückgesetzt werden kann.
	 */
	private final int resetValue;
	public Counter(){
		this(0);
	}
	public Counter(int value){
		this.value = value;
		this.resetValue = value;
	}
	public void increment(){
		this.value++;
	}
	public void decrement(){
		this.value--;
	}
	public void reset(){
		this.value = this.resetValue;
	}
	public int show(){
		return this.value;
	}
}
