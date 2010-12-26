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
import java.util.List;


public class ObjectBrowser {

	List<Method> decMeth = new ArrayList<Method>();
	
	private Field[] fields;
	private Constructor<?>[] constructors;
	private Method[] methods;
	private Annotation[] annotations;
	private Class<?>[] classes;
	
	
	public Object setObject(Object obj) {
		return obj;
	}
	
	public void searchThroughClass() {
		for(Method met : Class.class.getDeclaredMethods()) {
			if(met.getReturnType().isArray()) {
				if(met.getParameterTypes().length == 0) {
					if(Modifier.isPublic(met.getModifiers())) {
						if(met.getName().contains("Declared")) {
							decMeth.add(met);
						}
					}
				}
			}
		}
//		printList(decMeth);	
	}
	
	private static <TTargetType> TTargetType as(Object o, Class<TTargetType> clazz) {
	    //...
	    if(null == o || null == clazz){
	      return null;
	    }else if(clazz.isAssignableFrom(o.getClass())){
	      return clazz.cast(o);  
	    }else{
	      return null;
	    }
	}

	private void chooseType(Object obj, Method met, Object testObj)
		throws IllegalAccessException, InvocationTargetException {
		if(testObj.getClass().getName().equals(Annotation[].class.getName())) {
			// TODO No Annotations as return value - why ?
//			System.out.println(met);
//			System.out.println("TEST");
			this.annotations = as(met.invoke(obj.getClass()), Annotation[].class);
			printContent((Object[])this.annotations);
			fillIt(this.annotations);
		} else if(testObj.getClass().getName().equals(Class[].class.getName())) {
			this.classes = as(met.invoke(obj.getClass()), Class[].class);
			fillIt(this.classes);
		} else if(testObj.getClass().getName().equals(Constructor[].class.getName())) {
			this.constructors = as(met.invoke(obj.getClass()), Constructor[].class);
			fillIt(this.constructors);
		} else if(testObj.getClass().getName().equals(Field[].class.getName())) {
			this.fields = as(met.invoke(obj.getClass()), Field[].class);
			fillIt(this.fields);
		} else if(testObj.getClass().getName().equals(Method[].class.getName())) {
			this.methods = as(met.invoke(obj.getClass()), Method[].class);
			fillIt(this.methods);
		}
	}
	
	private StringBuilder fillIt(Object[] objArr) {
		StringBuilder sb = new StringBuilder();
		for(Object obj : objArr) {
			sb.append("-> ");
			sb.append(obj);	
		}
		System.out.println(sb);
		return sb;
	}
	
	/*
	 *  public java.lang.annotation.Annotation[] java.lang.Class.getDeclaredAnnotations()
	 *	public java.lang.Class[] java.lang.Class.getDeclaredClasses() throws java.lang.SecurityException
	 *	public java.lang.reflect.Constructor[] java.lang.Class.getDeclaredConstructors() throws java.lang.SecurityException
	 *	public java.lang.reflect.Field[] java.lang.Class.getDeclaredFields() throws java.lang.SecurityException
	 *	public java.lang.reflect.Method[] java.lang.Class.getDeclaredMethods() throws java.lang.SecurityException
	 *
	 */
	public void reflectObject(Object obj) throws InstantiationException, SecurityException, NoSuchFieldException, IllegalArgumentException, IllegalAccessException, InvocationTargetException, NoSuchMethodException {

//		Annotation[] ann = obj.getClass().getAnnotations();
//		printContent(ann);
		
		for(Method met : decMeth) {
			Object testObj = met.invoke(obj.getClass());
			chooseType(obj, met, testObj);
			
			// TODO How to zoom and in which method ?
		}
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

	@Override
	public String toString() {
		return "ObjectBrowser [annotaions=" + Arrays.toString(annotations)
				+ ", classes=" + Arrays.toString(classes) + ", constructors="
				+ Arrays.toString(constructors) + ", decMeth=" + decMeth
				+ ", fields=" + Arrays.toString(fields) + ", methods="
				+ Arrays.toString(methods) + "]";
	}
}
		
		
//		Method mt = Class.class.getDeclaredMethod("getDeclaredFields");
//		Field[] ob = (Field[]) mt.invoke(obj.getClass());
//		
//		//switch case mit enums
//		System.out.println(ob.getClass().getName());
//		System.out.println(Field[].class);

//		Object testObj = mt.invoke(obj.getClass());
//		chooseType(obj, mt, testObj);
		
//		chooseType(obj, mt, ob);
//		
//		printContent(this.fields);
//		Field[] b = as(mt.invoke(obj.getClass()), Field[].class);
//		
//		System.out.println(ob.getClass().isArray());
//		System.out.println(mt.getReturnType());
//		Method[] m = ob.getClass().getDeclaredMethods();
//		printContent(ob);
//		printContent(b);
//		printContent(fields);
//		printContent(methods);
			
//				Object annotaions = met.invoke(obj.getClass());
//				printContent(annotaions);
				
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
//				ObjectContent oc = new ObjectContent();
//				Field[] fld = new Field[1];
//				fld = oc.getClass().getDeclaredFields();
//				fld[0] = this.getClass().getField("methods");
//				fld[1] = this.getClass().getDeclaredField("annotaions");
//				Field fld1 = this.getClass().getField("methods");
//				System.out.println(fld1.getType());
//				for(int i = 0; i < fld.length; i++) {
//					System.out.println(fld[i].getType());
//				}
				
//				fld[0].setAccessible(true);
//				System.out.println(oc.annotations.getClass().isArray());
//				System.out.println(oc.annotations.getClass());
//				System.out.println(fld[0].getClass().isArray());
//				System.out.println(fld[0].getClass());
//				System.out.println(oc.annotations.getClass().);
//				System.out.println(fld[0].getType().isArray());
				
				
//				Annotation[] tmp = (Annotation[]) fld[0].get(oc.annotations);
//				tmp = (Annotation[]) met.invoke(obj);
				
//				System.out.println(fld.length);
//				System.out.println(fld[0].getName());
//				System.out.println(fld[0].get(oc));
//				System.out.println("TEST");
//				fld[0].set(oc.fields, Class.class.getFields());
				
//				System.out.println("--" + oc.fields);
				
//				if (fld[0].get(oc) instanceof Annotation[] ? true : false) {
//					System.out.println("TEst");
//				}
//				(Annotation[]) fld[0] = (Annotation[]) met.invoke(obj.getClass();
//				oc.annotaions = (Annotation[]) met.invoke(obj.getClass());
//				oc.iterator().next();
						
//				for(Field fld : oc.getClass().getDeclaredFields()) {
//					Class<?> cl = fld.getType();
//					if(fld.getType().isArray()) {
//						fld = fld.getClass().newInstance(); 
//						fld.set(fld, met.invoke(obj.getClass()));
//						break;
//					}
//					System.out.println(oc.annotaions);
//					
//					ob = met.invoke(obj.getClass());
//				}
					
//				for(Iterator<ObjectContent> oc = content.iterator(); oc.hasNext();) { // not functional
//					System.out.println(met.invoke(obj.getClass()));
//					oc.next().annotaions = 
//					annotaions = (Annotation[]) met.invoke(obj.getClass());
//					System.out.println(oc.annotaions[0]);
//				}
//			Annotation[] ann = obj instanceof Annotation[] ? (Annotation[]) obj : null;
//			if (ann != null) {
//				oc.annotaions = ann;
//			}
//		printList(content);
//	}

	
//	private void printList(List<? extends Class<?>> decMeth) {
//		for(Class<?> met : decMeth) {
//			System.out.println(met);
////			for(Annotation ann : met.annotations)
////			System.out.println(ann);
//		}
//	}
	

