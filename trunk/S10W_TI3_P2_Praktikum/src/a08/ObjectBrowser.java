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
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;


public class ObjectBrowser {

	List<ObjectContent> content = new ArrayList<ObjectContent>();
	List<Method> decMeth = new ArrayList<Method>();
	
	Field[] fields;
	Constructor<?>[] constructors;
	Method[] methods;
	Annotation[] annotaions;
	Class<?>[] classes;
	
	
	public Object setObject(Object obj) {
		return obj;
	}
	
	public void searchThroughClass() {
		for(Method met : Class.class.getDeclaredMethods()) {
			if(met.getReturnType().isArray()) {
				if(met.getParameterTypes().length == 0) {
					if(met.getModifiers() == Modifier.PUBLIC) {
						decMeth.add(met);
					}
				}
			}
		}
//		printList(decMeth);	
	}
	
	
	/*
	 // TODO How to filter getX methods without getDeclaredX ?
	 * 
public java.lang.annotation.Annotation[] java.lang.Class.getAnnotations()
public java.lang.Class[] java.lang.Class.getClasses()
public java.lang.reflect.Constructor[] java.lang.Class.getConstructors() throws java.lang.SecurityException
public java.lang.annotation.Annotation[] java.lang.Class.getDeclaredAnnotations()
public java.lang.Class[] java.lang.Class.getDeclaredClasses() throws java.lang.SecurityException
public java.lang.reflect.Constructor[] java.lang.Class.getDeclaredConstructors() throws java.lang.SecurityException
public java.lang.reflect.Field[] java.lang.Class.getDeclaredFields() throws java.lang.SecurityException
public java.lang.reflect.Method[] java.lang.Class.getDeclaredMethods() throws java.lang.SecurityException
public java.lang.Object[] java.lang.Class.getEnumConstants()
public java.lang.reflect.Field[] java.lang.Class.getFields() throws java.lang.SecurityException
public java.lang.reflect.Type[] java.lang.Class.getGenericInterfaces()
public java.lang.reflect.Method[] java.lang.Class.getMethods() throws java.lang.SecurityException
public java.lang.reflect.TypeVariable[] java.lang.Class.getTypeParameters()
	 *
	 */
	public void reflectObject(Object obj) {
		
		for(Method met : decMeth) {
			try {
//				switch (met.getReturnType()) {
//					case Annotation[] : 
//						annotaions = met.invoke(obj.getClass();
//					break;
//					case Class[] : 
//						classes = met.invoke(obj.getClass();
//					break;
//					default :;
//				}
				
//				System.out.println(met);
//				System.out.println(met.invoke(obj.getClass()));
				// TODO How to iterate sync with the data structure of Arrays ?
				for(Iterator<ObjectContent> oc = content.iterator(); oc.hasNext();) { // not functional
					System.out.println(met.invoke(obj.getClass()));
					oc.next().annotaions = 
					annotaions = (Annotation[]) met.invoke(obj.getClass());
//					System.out.println(oc.annotaions[0]);
				}
			} catch (IllegalArgumentException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InvocationTargetException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
//			Annotation[] ann = obj instanceof Annotation[] ? (Annotation[]) obj : null;
//			if (ann != null) {
//				oc.annotaions = ann;
//			}
		}
		printList(content);
	}
	
	public void searchContent(Object obj) {
		//only print on console for debug
//		printContent(this.fields = searchFields(obj));
//		printContent(this.constructors = searchConstructors(obj));
//		printContent(this.methods = searchMethods(obj));
//		printContent(this.annotaions = searchAnnotations(obj));
//		printContent(this.classes = searchClasses(obj));
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
	
	private void printList(List<? extends ObjectContent> decMeth) {
		for(ObjectContent met : decMeth) {
			for(Annotation ann : met.annotaions)
			System.out.println(ann);
		}
	}
	
	private void printContent(Object... obj) {
		System.out.println(obj.length);
		for(Object ob : obj) {
			System.out.println(ob + "\n");
		}
	}

	@Override
	public String toString() {
		return "ObjectBrowser [annotaions=" + Arrays.toString(annotaions)
				+ ", classes=" + Arrays.toString(classes) + ", constructors="
				+ Arrays.toString(constructors) + ", content=" + content
				+ ", decMeth=" + decMeth + ", fields="
				+ Arrays.toString(fields) + ", methods="
				+ Arrays.toString(methods) + "]";
	}
	
}
