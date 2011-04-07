package tester.klausur.InverseComparator;

import java.util.Comparator;

public class InverseComparator<T extends Comparable<T>> implements Comparator<T> { 
	
	public int compare(T t1, T t2) { 
		return t2.compareTo(t1); 
	}
}
