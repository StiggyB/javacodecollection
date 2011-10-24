package tester.klausur.generics;

public class GenGetterSetter<T> {

	private T t;
	
	public GenGetterSetter(T t) {
		this.t = t;
	}
	
	public T getT() {
		return t;
	}

	public void setT(T t) {
		this.t = t;
	}
}
