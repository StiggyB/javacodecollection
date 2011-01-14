package a10;
/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 10<br>
 * 
 * Version: V0<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, HTML Elements by Martin Slowikowski
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

import java.util.ArrayList;
import java.util.List;

/**
 * This class creates a Christmas Tree
 * with a recursion algorithm.
 * 
 *
 */
public class ChristmasTreePattern {	
	
	/**
	 * Creates a Christmas Tree structure in a recursion way.
	 * The method builds a StringBuilder with HTML-Tags to align it.
	 * 
	 * @param n count of bits
	 * @return sb complete Christmas Tree
	 */
	public StringBuilder createChrisTree(int n) {
		List<List<String>> lines = new ArrayList<List<String>>();
		List<String> line = new ArrayList<String>();
		if(n >= 1) {
			//n == 1
			line.add("0");
			line.add("1");
			lines.add(line);
		}
		getChrisTreeLines(lines, n);
		StringBuilder sb = new StringBuilder();
		sb.append("<html><body><p align=\"center\">");
		for(List<String> accLine : lines) {
			for(String str : accLine) {
				sb.append(str + " ");
			}
			sb.append("<br>");
		}
		sb.append("</p></body></html>");
		
		return sb;
	}
	
	/**
	 * Add a specific count of Strings together
	 * in order of this pattern.
	 * 
	 * 			  's2'0 ... 'st'0
	 * 		's1'0 's1'1 ... 'st-1'1 'st'1
	 * 
	 * If t = 1 drop the first line of the pattern.
	 * 
	 * @param lines is the list to collect the pattern
	 * @param n is the number of iterations
	 */
	public void getChrisTreeLines(List<List<String>> lines, int n) {
		if(n > 1) {
			
			List<List<String>> nextLines = new ArrayList<List<String>>();
			int t = 0;
			for(List<String> currLine : lines) {
				t = currLine.size();
				//test the first line == 1 Element
				if(t == 1) {
					
					//true -> start with the second line of the pattern
					List<String> nextLine = new ArrayList<String>();
					nextLine.add(currLine.get(0).concat("0"));
					for(int i = 0; i < currLine.size(); i++) {
						nextLine.add(currLine.get(i).concat("1"));  //no function - why?
					}
					nextLines.add(nextLine);
								
				} else {
					
					//false -> start normal with the first line...
					List<String> nextLine = new ArrayList<String>();
					for(int i = 1; i < currLine.size(); i++) {
						nextLine.add(currLine.get(i).concat("0"));  //no function - why?
					}
					nextLines.add(nextLine);
					
					//use the second line of the pattern
					nextLine = new ArrayList<String>();
					nextLine.add(currLine.get(0).concat("0"));
					for(int i = 0; i < currLine.size(); i++) {
						nextLine.add(currLine.get(i).concat("1"));					
					}
					nextLines.add(nextLine);
				}
			}
			lines.clear();
			lines.addAll(nextLines);
			n--;
			getChrisTreeLines(lines, n);
		}	
	}
	
	
	/**
	 * Method for Debugging
	 * 
	 * @param list to print
	 */
//	private void printList(List<List<String>> list) {
//		for(List<String> line : list) {
//			System.out.println(line);
//		}
//	}
	
}
