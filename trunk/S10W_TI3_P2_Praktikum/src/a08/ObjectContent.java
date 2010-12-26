package a08;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Arrays;

public class ObjectContent { //implements Iterable<ObjectContent> {
	//not used - just a idea
	public Annotation[] annotations = new Annotation[1];
	public Field[] fields = new Field[1];
	public Constructor<?>[] constructors;
	public Method[] methods;
	public Class<?>[] classes;
	
	@Override
	public String toString() {
		return "ObjectContent [annotations=" + Arrays.toString(annotations)
				+ ", classes=" + Arrays.toString(classes) + ", constructors="
				+ Arrays.toString(constructors) + ", fields="
				+ Arrays.toString(fields) + ", methods="
				+ Arrays.toString(methods) + "]";
	}	
	
}
