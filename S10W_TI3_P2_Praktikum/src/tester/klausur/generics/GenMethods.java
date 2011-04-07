package tester.klausur.generics;

import java.util.List;

import tester.klausur.FactoryPattern.A;

public class GenMethods {

	
	public static <T> void test(T t) { //no access to T Type from C<T>...
		t.toString();
	}
	
	public <E> void test(List<? super E> list) { //E and T? - no access to T Type from C<T>...
		list.toString();
	}
	
	public static <E extends A> void create2(E e) {
		System.out.println("Created with create2  " + e);
		e.test();		
	}
	
	public static <T0, T1 extends T0> T0 m4(T0 t0,T1 t1) { //Avoid Typ Inferenz 
		return Math.random() < 0.5 ? t0 :t1; 
	}
	
}
