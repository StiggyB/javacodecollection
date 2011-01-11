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
	private Object obj;
	
	public ObjectBrowser(Object obj) {
		this.obj = obj;
	}
	
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
//		System.out.println(sb);
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
			if(obj != null) {
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
		if(met.getParameterTypes().length == 0 && met.getReturnType().isPrimitive() && this.obj.equals(obj)) {
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
		sb.append("\n Field value: \n\t");
		if(fld.getType().isPrimitive() && Modifier.toString(fld.getModifiers()).contains(Modifier.toString(Modifier.STATIC))) {
			sb.append(fld.get(obj));
		} else if(!(fld.getType().isArray()) && this.obj.equals(obj)) {
			sb.append(fld.get(obj));		
		} else {
			sb.append("unknown");
		}
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
		
		

