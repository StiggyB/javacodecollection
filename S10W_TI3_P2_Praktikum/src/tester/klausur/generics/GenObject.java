package tester.klausur.generics;

@SuppressWarnings("unchecked")
public class GenObject<T> {

	private T t;
	
	public GenObject() {
		this.t = (T) new Object();
	}
}
