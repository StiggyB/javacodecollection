package a08;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Iterator;

public class ObjectContent implements Iterable<ObjectContent> {
	//not used - just a idea
	Field[] fields;
	Constructor<?>[] constructors;
	Method[] methods;
	Annotation[] annotaions;
	Class<?>[] classes;
	
	
	@Override
	public Iterator<ObjectContent> iterator() {
		// TODO Auto-generated method stub
		return list.;
	}	
	
}
