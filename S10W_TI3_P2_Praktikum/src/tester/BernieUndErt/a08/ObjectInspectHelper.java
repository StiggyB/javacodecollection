package tester.BernieUndErt.a08;

/**
 * 
 * @author Bernie und Ert
 * 
 *         In dieser Klasse befinden sich die Methoden, zum Inspizieren von
 *         Objekten. Die Methoden sind ausgelagert aus der ExplorerTree Klasse, 
 *         um diese �bersichtlicher zu gestalten.
 * 
 */

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

public class ObjectInspectHelper {
	
	
	public String printClassModifiers(Class<?> c) {
		return c.getModifiers() == 0 ? "no class-modifier (Package)" : Modifier.toString(c.getModifiers());
	}
	
	public String printMethodModifiers(Method m) {
		return Modifier.toString(m.getModifiers());
	}

	public String printSuperclasses(Object o) {
		StringBuilder sb = new StringBuilder();
		Class<?> subclass = o.getClass();
		Class<?> superclass = subclass.getSuperclass();
		while (superclass != null) {
			String className = superclass.getName();
			sb.append("\n").append("  - ").append(className);
			subclass = superclass;
			superclass = subclass.getSuperclass();
		}
		sb.append(" (Superklasse)\n");
		return sb.toString();
	}
	
	public String printInterfaces(Object o){
		StringBuilder sb = new StringBuilder();
		Class<?> c = o.getClass();
		Class<?>[] theInterfaces = c.getInterfaces();
		if(theInterfaces.length != 0){
		sb.append("\n");
		for (int i = 0; i < theInterfaces.length; i++) {
			sb.append("  - ").append(theInterfaces[i].getCanonicalName()).append("\n");
		}
		return sb.toString();
		}
		return "No Interfaces implemented\n";
	}
	
	public String printConstructors(Object o) {
		StringBuilder sb = new StringBuilder();
		Class<?> c = o.getClass();
		Constructor<?>[] theConstructors = c.getDeclaredConstructors();
		sb.append("\n");
		for (int i = 0; i < theConstructors.length; i++) {
			sb.append("  - ").append(theConstructors[i]).append("\n");
		}
		return sb.toString();
	}
	
	public String printFieldInfos(Field field){
		StringBuilder sb = new StringBuilder();
		Class<?> typeClass = field.getType();
		sb.append("- Name: " + field.getName() + "\n- Type: " + typeClass.getName() + "\n- Modifier(s): " + printClassModifiers(typeClass));
		return sb.toString();
	}
	
	public String printMethod(Method method) {
		StringBuilder sb = new StringBuilder();
		sb.append("- Name: " + method.getName());
		sb.append("\n- Modifier(s): " + printMethodModifiers(method));
		sb.append("\n- R�ckgabetyp: " + method.getReturnType().getSimpleName());
		Class<?>[] parameterTypes = method.getParameterTypes();
		sb.append("\n- �bergabeparamtertyp:");
		for (int k = 0; k < parameterTypes.length; k++) {
			sb.append(" " + parameterTypes[k].getSimpleName() + " ");
		}
		return sb.toString();
	}

}
