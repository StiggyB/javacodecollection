package tester;

import java.util.ArrayList;
import java.util.List;

public class ChristmasTreePattern {	
	
	/**
	 * Creates a Christmas Tree structure in a recursion way.
	 * 
	 * @param n
	 * @return
	 */
	public List<List<String>> createChrisTree(int n) {
		List<List<String>> lines = new ArrayList<List<String>>();
		List<String> line = new ArrayList<String>();
		if(n >= 1) {
			line.add("0");
			line.add("1");
			lines.add(line);
		}
		getChrisTreeLines(lines, n);
		//TODO Change the return value for the View
		
		return lines;
	}
	
	/**
	 * 
	 * Add a specific count of Strings together
	 * in order of this pattern.
	 * 
	 * 			  's2'0 ... 'st'0
	 * 		's1'0 's1'1 ... 'st-1'1 'st'1
	 * 
	 * If t = 1 drop the first line of the pattern.
	 * 
	 * @param lines
	 * @param n
	 */
	public void getChrisTreeLines(List<List<String>> lines, int n) {
		if(n > 1) {
			//TODO New line necessary - the tree have to grow up!
			List<List<String>> nextLines = new ArrayList<List<String>>();
			int t = 0;
			for(List<String> currLine : lines) {
				t = currLine.size();
				//test the first line == 1 Element
				if(t == 1) {
					
					//true -> start with the second line of the pattern
					System.out.println("true");
					List<String> nextLine = new ArrayList<String>();
					nextLine.add(currLine.get(0).concat("0"));
					for(int i = 0; i < currLine.size(); i++) {
						nextLine.add(currLine.get(i).concat("1"));  //no function - why?
					}
					nextLines.add(nextLine);
					
					
				} else {
					
					//false -> start normal with the first line...
					System.out.println("false");
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
			printList(nextLines);
		
			n--;
			getChrisTreeLines(nextLines, n);
		}
	}
	

	/**
	 * @param list
	 * @return
	 */
	int getCountOfElements(List<String> list) {
		int t = 0;
		for(; list.get(t) != "\n"; t++) {
		}
		return t;
	}
	
	/**
	 * @param list
	 */
	private void printList(List<List<String>> list) {
		for(List<String> line : list) {
			System.out.println(line);
		}
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		ChristmasTreePattern cTree = new ChristmasTreePattern();
		cTree.createChrisTree(9);
	}
}
