package tester.a08;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class DiscoverClass {
    public String x;

    DiscoverClass(String s) {
        this.x = s;
    }

    static void printSuperclasses(Object o) {
        Class<?> subclass = o.getClass();
        Class<?> superclass = subclass.getSuperclass();
        while (superclass != null) {
            String className = superclass.getName();
            System.out.println(className);
            subclass = superclass;
            superclass = subclass.getSuperclass();
        }
    }

    public static void main(String[] args) {
        DiscoverClass dc = new DiscoverClass("DiscoverClass");
        for (Field c : dc.getClass().getFields()) {
            System.out.println(c);
        }
        for (Constructor<?> c : dc.getClass().getConstructors()) {
            System.out.println(c);
        }
        for (Method c : dc.getClass().getDeclaredMethods()) {
            System.out.println(c);
        }
        printSuperclasses(dc);

    }
}
