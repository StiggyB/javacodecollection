package tester.a08;
@SuppressWarnings("all")
public class Clazz {

	private class Memeber{
		
	}
	
	interface I1 {
		
	}
	
	public int value;
	public double dvalue;
	private int integer;
	String str;
	
	//default Constructor
	public Clazz(int value){
		this.value = value;
		this.integer = value;
	}
	
	public int getValue() {
		return this.value;
	}
	
	public void setValue(int value) {
		this.value = value;
	}

	@Override
	public String toString() {
		return "Clazz [dvalue=" + dvalue + ", value=" + value + "]";
	}
	
}
