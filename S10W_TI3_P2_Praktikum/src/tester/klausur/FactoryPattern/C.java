package tester.klausur.FactoryPattern;

public class C<T extends A & I1 & I2> {
	private T t;
	final Factory<T> factory;
	public C(Factory<T> f) {
		this.factory = f;
	}
	
	public T newOne() {		
		return this.factory.create();
	}
	
	public static void main(String[] args) {
		C<A> c = new C<A>(new Factory<A>() {
				public A create() {
					return new A(5);
				}
		});
		A a = c.newOne();
		System.out.println("Created with Factory " + a);		
	}
	
	public static <T0, T1 extends A & I1 & I2> void m4(T0 t0,T1 t1) { //Avoid Typ Inferenz 
//		return Math.random() < 0.5 ? t0 :t1; 
	}
}	



	/*
	 * 		
		T newT = f.create();
		System.out.println("Created with Factory  " + newT.toString());
		
		T[] tCast = (T[]) (new Object[10]);

		System.out.println("Created with Cast  " + tCast.toString());
		
		//C<T> c = new C[10]; //How to create a generic Array?
		
		Object tObj = new Object();
		System.out.println("Created with Object  " + tObj.toString());
	 */

