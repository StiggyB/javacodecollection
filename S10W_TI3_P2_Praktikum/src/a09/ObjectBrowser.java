package a09;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 09<br>
 * 
 * Version: V0.1<br>
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
import java.util.List;

/**
 * This class build the Model of the a09.ObjectBrowser .
 * It provides almost all properties of a specific Object.
 * 
 */
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

	/**
	 * This method search through the class Class and fill 
	 * the relevant reflection methods in a09.ObjectBrowser.decMeth
	 * 
	 * @see ObjectBrowser#decMeth
	 */
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
	
	/**
	 * This method realize a dynamic cast if the generic type
	 * Class<TTargetType> clazz is right.
	 * 
	 * @param <TTargetType>
	 * @param o
	 * @param clazz
	 * @return <TTargetType> TTargetType is o casted to the right Class or null 
	 * source: 
	 * http://www.tutorials.de/java/271567-variabler-cast-und-klassendefinition-java-wie-php.html
	 */
	public static <TTargetType> TTargetType as(Object o, Class<TTargetType> clazz) {
	    if(null == o || null == clazz){
	    	return null;
	      
	    }else if(clazz.isAssignableFrom(o.getClass())){
	      return clazz.cast(o);  
	    }else{
	      return null;
	    }
	}

	
	/**
	 * This method choose the right type for the reflection methods
	 * and fill the right arrays with the return value.
	 * 
	 * @param obj
	 * @param met
	 * @param testObj
	 * @throws IllegalAccessException
	 * @throws InvocationTargetException
	 * @see a09.ObjectBrowser.as
	 * @see a09.ObjectBrowser.annotations
	 * ...
	 */
	private void chooseType(Object obj, Method met, Object testObj)
		throws IllegalAccessException, InvocationTargetException {
		if(testObj.getClass().getName().equals(Annotation[].class.getName())) {
			this.annotations = as(met.invoke(obj.getClass()), Annotation[].class);
		} else if(testObj.getClass().getName().equals(Class[].class.getName())) {
			this.classes = as(met.invoke(obj.getClass()), Class[].class);
		} else if(testObj.getClass().getName().equals(Constructor[].class.getName())) {
			this.constructors = as(met.invoke(obj.getClass()), Constructor[].class);
		} else if(testObj.getClass().getName().equals(Field[].class.getName())) {
			this.fields = as(met.invoke(obj.getClass()), Field[].class);
		} else if(testObj.getClass().getName().equals(Method[].class.getName())) {
			this.methods = as(met.invoke(obj.getClass()), Method[].class);
		}
	}
	
	/**
	 * A method to iterate over the reflection
	 * methods in a09.ObjectBrowser.decMeth
	 * 
	 * @param obj
	 * @see ObjectBrowser#chooseType
	 * @see ObjectBrowser#searchThroughClass
	 */
	public void reflectObject(Object obj) {

		if(obj != null) {
			for(Method met : decMeth) {	
				try {
					Object testObj = met.invoke(obj.getClass());
					chooseType(obj, met, testObj);
					
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
			} 
		}
	}
	
	
	/**
	 * This method build a summary of almost all class properties
	 * 
	 * @param obj
	 * @return class properties as StringBuilder
	 */
	public StringBuilder getClassInfo(Object obj) {
		StringBuilder sb = new StringBuilder();
		Class<?> c = obj.getClass();
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
	
	/**
	 * This method build a summary of almost all method properties 
	 * 
	 * @param met
	 * @param obj
	 * @return method properties as StringBuilder
	 * @throws IllegalArgumentException
	 * @throws IllegalAccessException
	 * @throws InvocationTargetException
	 */
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
		return sb;
	}
	
	/**
	 * This method build a summary of almost all field properties
	 * 
	 * @param fld
	 * @param obj
	 * @return field properties as StringBuilder
	 * @throws IllegalArgumentException
	 * @throws IllegalAccessException
	 */
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
		return sb;
	}
	
	/*
	 * These 2 Methods only used for Debugging.
	 */
	
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
}
		
		

