package tester.klausur.generics;

public class GenObjGetterSetter<T> {

	private Object t;
	
	public GenObjGetterSetter() {
		this.t = new Object();
	}
	
	@SuppressWarnings("unchecked")
	public T getT() {
		return (T) t;
	}
	
	public void setT(T t) {
		this.t = t;
	}
}
