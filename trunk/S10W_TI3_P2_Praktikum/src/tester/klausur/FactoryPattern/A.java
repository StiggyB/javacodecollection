package tester.klausur.FactoryPattern;

public class A implements I1, I2 {

	int i;
	
	public A(int i) {
		this.i = i;
	}
	
	public void test() {
		System.out.println("Do it!");
	}
}
