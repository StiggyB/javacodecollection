package tester.a08;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.List;

@SuppressWarnings("all")
public class ObjectBrowserTest {

	
	private Field[] fields;
	private Constructor<?>[] constructors;
	private Method[] methods;
	private Annotation[] annotaions;
	private Class<?>[] classes;
	
	public void searchContent(Object obj) {
		//only print on console for debug
		printContent(this.fields = searchFields(obj));
		printContent(this.constructors = searchConstructors(obj));
		printContent(this.methods = searchMethods(obj));
		printContent(this.annotaions = searchAnnotations(obj));
		printContent(this.classes = searchClasses(obj));
		printContent();
		
	}
	
	private Field[] searchFields(Object obj) {
		Field[] fields = new Field[1];
		for(Field fld : obj.getClass().getDeclaredFields()) {
			if(fld.getModifiers() == Modifier.PRIVATE) {
				fld.setAccessible(true);
				//if(more content -> zoom) ...
			}
			fields = obj.getClass().getDeclaredFields();
		}
		return fields;
	}
	
	private Constructor<?>[] searchConstructors(Object obj) {
		Constructor<?>[] constr = new Constructor[1];
		for(Constructor<?> con : obj.getClass().getDeclaredConstructors()) {
			if(con.getParameterTypes().length != 0) {
				Class<?>[] arr = con.getParameterTypes();
				//if(more content -> zoom) ...
			}
			if(con.getModifiers() == Modifier.PRIVATE) {
				con.setAccessible(true);
			}
			constr = obj.getClass().getDeclaredConstructors();
		}
		return constr;
	}
	
	private Method[] searchMethods(Object obj) {
		Method[] methods = new Method[1];
		for(Method meth : obj.getClass().getDeclaredMethods()) {
			if(meth.getParameterTypes().length != 0) {
				Class<?>[] arr = meth.getParameterTypes();
				//if(more content -> zoom) ...
			}
			if(meth.getModifiers() == Modifier.PRIVATE) {
				meth.setAccessible(true);
			}
			methods = obj.getClass().getDeclaredMethods();
		}
		return methods;
	}
	
	private Annotation[] searchAnnotations(Object obj) {
		Annotation[] anno = new Annotation[1];
		System.out.println(obj.getClass().getDeclaredAnnotations());
		for(Annotation ann: obj.getClass().getDeclaredAnnotations()) {
			anno = obj.getClass().getDeclaredAnnotations();
		}
		return anno;
	}
	
	private Class<?>[] searchClasses(Object obj) {
		Class<?>[] clss = new Class[1];
		for(Class cls : obj.getClass().getDeclaredClasses()) {
			//if(cls more content -> zoom) ...
			clss = obj.getClass().getDeclaredClasses();
		}
		return clss;
	}
	
	private void printList(List<Method> decMeth) {
		for(Method met : decMeth) {
			System.out.println(met);
//			for(Annotation ann : met.annotations)
//			System.out.println(ann);
		}
	}
	
	private void printContent(Object... obj) {
		System.out.println(obj.length);
		for(Object ob : obj) {
			System.out.println(ob.toString() + "\n");
		}
	}
}
