package a09;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;


/**
 * This annotation is for testing purposes
 *
 */
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface TestAnno {
	
	String value() default "null";
	
	double id() default Double.NaN;
	
	Class<? extends Exception> exception();
}
