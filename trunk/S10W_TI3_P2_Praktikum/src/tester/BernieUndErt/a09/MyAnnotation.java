package tester.BernieUndErt.a09;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * Dies ist eine recht "nutzlose" Beispielannotation zum Testen
 * 
 * @author Bernie und Ert
 * @version 1.0
 */
@Retention(RetentionPolicy.RUNTIME)
public @interface MyAnnotation {
	public String name();

	public String value();

}
