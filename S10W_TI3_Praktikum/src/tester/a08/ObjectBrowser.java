package tester.a08;
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

	
	public List<Method> getDecMeth() {
		return decMeth;
	}

	public void setDecMeth(List<Method> decMeth) {
		this.decMeth = decMeth;
	}

	public Field[] getFields() {
		return fields;
	}

	public void setFields(Field[] fields) {
		this.fields = fields;
	}

	public Constructor<?>[] getConstructors() {
		return constructors;
	}

	public void setConstructors(Constructor<?>[] constructors) {
		this.constructors = constructors;
	}

	public Method[] getMethods() {
		return methods;
	}

	public void setMethods(Method[] methods) {
		this.methods = methods;
	}

	public Annotation[] getAnnotations() {
		return annotations;
	}

	public void setAnnotations(Annotation[] annotations) {
		this.annotations = annotations;
	}

	public Class<?>[] getClasses() {
		return classes;
	}

	public void setClasses(Class<?>[] classes) {
		this.classes = classes;
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
	
	public static <TTargetType> TTargetType as(Object o, Class<TTargetType> clazz) {
	    if(null == o || null == clazz){
	    	System.out.println("Param == Null!");
	    	return null;
	      
	    }else if(clazz.isAssignableFrom(o.getClass())){
	      return clazz.cast(o);  
	    }else{
	    	System.out.println("Simple Null");
	      return null;
	    }
	}

	private void chooseType(Object obj, Method met, Object testObj)
		throws IllegalAccessException, InvocationTargetException {
		if(testObj.getClass().getName().equals(Annotation[].class.getName())) {
			this.annotations = as(met.invoke(obj.getClass()), Annotation[].class);
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
	
	public StringBuilder getClassInfo(Object obj) {
		StringBuilder sb = new StringBuilder();
		Class<?> c = obj.getClass();
		System.out.println(c);
		sb.append("Class \n");
		sb.append("\n Name: \n\t" + c.getSimpleName());
		sb.append("\n Modifier: \n\t" + Modifier.toString(c.getModifiers()));
		sb.append("\n Annotations: \n");
		for(Annotation ann : annotations) {
			sb.append("\t " + ann + "\n");
		}
		sb.append("\n Superclasses: \n");
		Class<?>  sClss = c.getSuperclass();
		while(sClss != null) {
			sb.append("\t " + sClss + "\n");
			sClss = sClss.getSuperclass();
		}
		sb.append("\n Interfaces (implemented): \n");
		for(Class<?> intFace : c.getInterfaces()) {
			sb.append("\t " + intFace + "\n");
		}
		sb.append("\n Constructors: \n");
		for(Constructor<?> constr : constructors) {
			sb.append("\t " + constr + "\n");
		}
		sb.append("\n Inner Classes/ Interfaces: ");
		for(Class<?> clss : classes) {
			sb.append("\n\t " + clss);
		}
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
	public void reflectObject(Object obj) {
		for(Method met : decMeth) {
			Object testObj = null;
			try {
				testObj = met.invoke(obj.getClass());
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
			try {
				chooseType(obj, met, testObj);
			} catch (IllegalAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InvocationTargetException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}	
			
		}
	}
	
	public StringBuilder zoomInMethod(Method met, Object obj) throws IllegalArgumentException, IllegalAccessException, InvocationTargetException {
		StringBuilder sb = new StringBuilder();
		sb.append("Method \n");
		sb.append("\n Name: \n\t" + met.getName());
		sb.append("\n Modifier: \n\t" + Modifier.toString(met.getModifiers()));
		sb.append("\n Returntype: \n\t" + met.getReturnType().getSimpleName());
		Class<?>[] paraTypes = met.getParameterTypes();
		sb.append("\n Parametertypes: \n");
		for(int i = 0; i < paraTypes.length; i++) {
			sb.append("\t" + paraTypes[i].getSimpleName() + "\n");
		}
		Annotation[] ann = met.getDeclaredAnnotations();
		sb.append("\n Annotations: \n");
		for(Annotation an : ann) {
			sb.append("\t" + an + "\n");
		}
		sb.append("\n Return value: \n");
		met.setAccessible(true);
		Object reVal = "unknown";
		if(met.getParameterTypes().length == 0) {
			reVal = met.invoke(obj);
		}
		sb.append("\t " + reVal + "\n");
		sb.append("\n");
		System.out.println(sb);
		return sb;
	}
	
	public StringBuilder zoomInField(Field fld, Object obj) throws IllegalArgumentException, IllegalAccessException {
		StringBuilder sb = new StringBuilder();
		sb.append("Field \n");
		sb.append("\n Name: \n\t" + fld.getName());
		sb.append("\n Type: \n\t" + fld.getType().getName());
		sb.append("\n Modifier: \n\t" + Modifier.toString(fld.getModifiers()));
		fld.setAccessible(true);
		sb.append("\n Field value: \n\t" + fld.get(obj)); 
		sb.append("\n");
		System.out.println(sb);	
		return sb;
	}
	
//	private void printList(List<Method> decMeth) {
//		for(Method met : decMeth) {
//			System.out.println(met);
//			for(Annotation ann : met.annotations)
//			System.out.println(ann);
//		}
//	}
//	
//	private void printContent(Object... obj) {
//		System.out.println(obj.length);
//		for(Object ob : obj) {
//			System.out.println(ob.toString() + "\n");
//		}
//	}

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
	

//EVT DOPPELT

//Method mt = Class.class.getDeclaredMethod("getDeclaredFields");
//Field[] ob = (Field[]) mt.invoke(obj.getClass());
//
////switch case mit enums
//System.out.println(ob.getClass().getName());
//System.out.println(Field[].class);

//Object testObj = mt.invoke(obj.getClass());
//chooseType(obj, mt, testObj);

//chooseType(obj, mt, ob);
//
//printContent(this.fields);
//Field[] b = as(mt.invoke(obj.getClass()), Field[].class);
//
//System.out.println(ob.getClass().isArray());
//System.out.println(mt.getReturnType());
//Method[] m = ob.getClass().getDeclaredMethods();
//printContent(ob);
//printContent(b);
//printContent(fields);
//printContent(methods);
	
//		Object annotaions = met.invoke(obj.getClass());
//		printContent(annotaions);
		
//		switch (met.getReturnType()) {
//			case Annotation[] : 
//				annotaions = met.invoke(obj.getClass();
//			break;
//			case Class[] : 
//				classes = met.invoke(obj.getClass();
//			break;
//			default :;
//		}
		
//		System.out.println(met);
//		System.out.println(met.invoke(obj.getClass()));
		// TODO How to iterate sync with the data structure of Arrays ?
//		ObjectContent oc = new ObjectContent();
//		Field[] fld = new Field[1];
//		fld = oc.getClass().getDeclaredFields();
//		fld[0] = this.getClass().getField("methods");
//		fld[1] = this.getClass().getDeclaredField("annotaions");
//		Field fld1 = this.getClass().getField("methods");
//		System.out.println(fld1.getType());
//		for(int i = 0; i < fld.length; i++) {
//			System.out.println(fld[i].getType());
//		}
		
//		fld[0].setAccessible(true);
//		System.out.println(oc.annotations.getClass().isArray());
//		System.out.println(oc.annotations.getClass());
//		System.out.println(fld[0].getClass().isArray());
//		System.out.println(fld[0].getClass());
//		System.out.println(oc.annotations.getClass().);
//		System.out.println(fld[0].getType().isArray());
		
		
//		Annotation[] tmp = (Annotation[]) fld[0].get(oc.annotations);
//		tmp = (Annotation[]) met.invoke(obj);
		
//		System.out.println(fld.length);
//		System.out.println(fld[0].getName());
//		System.out.println(fld[0].get(oc));
//		System.out.println("TEST");
//		fld[0].set(oc.fields, Class.class.getFields());
		
//		System.out.println("--" + oc.fields);
		
//		if (fld[0].get(oc) instanceof Annotation[] ? true : false) {
//			System.out.println("TEst");
//		}
//		(Annotation[]) fld[0] = (Annotation[]) met.invoke(obj.getClass();
//		oc.annotaions = (Annotation[]) met.invoke(obj.getClass());
//		oc.iterator().next();
				
//		for(Field fld : oc.getClass().getDeclaredFields()) {
//			Class<?> cl = fld.getType();
//			if(fld.getType().isArray()) {
//				fld = fld.getClass().newInstance(); 
//				fld.set(fld, met.invoke(obj.getClass()));
//				break;
//			}
//			System.out.println(oc.annotaions);
//			
//			ob = met.invoke(obj.getClass());
//		}
			
//		for(Iterator<ObjectContent> oc = content.iterator(); oc.hasNext();) { // not functional
//			System.out.println(met.invoke(obj.getClass()));
//			oc.next().annotaions = 
//			annotaions = (Annotation[]) met.invoke(obj.getClass());
//			System.out.println(oc.annotaions[0]);
//		}
//	Annotation[] ann = obj instanceof Annotation[] ? (Annotation[]) obj : null;
//	if (ann != null) {
//		oc.annotaions = ann;
//	}
//printList(content);
//}


//private void printList(List<? extends Class<?>> decMeth) {
//for(Class<?> met : decMeth) {
//	System.out.println(met);
////	for(Annotation ann : met.annotations)
////	System.out.println(ann);
//}
//}

