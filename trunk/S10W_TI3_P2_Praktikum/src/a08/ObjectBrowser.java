package a08;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 08<br>
 * 
 * Version: V0<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, PR2 Praktikum
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.List;


public class ObjectBrowser {

	List<ObjectContent> content = new ArrayList<ObjectContent>();
	
	Field[] fields;
	Constructor<?>[] constructors;
	Method[] methods;
	Annotation[] annotaions;
	Class<?>[] classes;
	
	
	public Object setObject(Object obj) {
		return obj;
	}
	
	public void searchContent(Object obj) {
		//only print on console for debug
		printContent(this.fields = searchFields(obj));
		printContent(this.constructors = searchConstructors(obj));
		printContent(this.methods = searchMethods(obj));
		printContent(this.annotaions = searchAnnotations(obj));
		printContent(this.classes = searchClasses(obj));
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
	
	
	
	
	private void printContent(Object[] obj) {
		for(Object ob : obj) {
			System.out.println(ob);
		}
	}

	@Override
	public String toString() {
		return "ObjectBrowser [toString()=" + super.toString() + "]";
	}
	

}
