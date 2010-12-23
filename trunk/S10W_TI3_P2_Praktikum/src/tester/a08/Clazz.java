package tester.a08;

public class Clazz {

	private class Memeber{
		
	}
	
	interface I1 {
		
	}
	
	int value;
	double dvalue;
	
	//default Constructor
	public Clazz(int value){
		this.value = value;
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
	
//	public static void main(String[] args) {
//		Clazz<T> clazz = new Clazz<T>();
//		clazz = Void.TYPE;
//		clazz = Integer.TYPE;
//		
//		clazz = int.class;
//		
//		Class<double[]> dClazz = double[].class;
//		Class<? extends String> sClazz = new String().getClass();+
//		
//		try {
//			clazz = Class.forName("java.lang.String");
//			Class.cast();
//			Class.asSubclass();
//		}
//		
//		System.out.println(Integer.class.getPackage());
//	}
	
}
