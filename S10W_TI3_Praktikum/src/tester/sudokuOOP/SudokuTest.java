package tester.sudokuOOP;


public class SudokuTest {

	public static void main(String[] args) {
		Sudoku gb = new Sudoku(
    	        2, 0, 0, 9, 0, 6, 0, 0, 4,
    	        0, 0, 5, 0, 7, 0, 9, 0, 0,
    	        0, 3, 0, 0, 0, 0, 0, 8, 0,
    	        0, 0, 3, 4, 0, 7, 8, 0, 0,
    	        8, 9, 0, 2, 0, 5, 0, 6, 3,
    	        0, 0, 7, 6, 0, 8, 2, 0, 0,
    	        0, 7, 0, 0, 0, 0, 0, 2, 0,
    	        0, 0, 8, 0, 6, 0, 1, 0, 0,
    	        3, 0, 0, 7, 0, 1, 0, 0, 8);
		if (gb.solve()) {
			System.out.println("SOLVED!!!");
		} else {
			System.out.println("Could not solve");
		}
	}
}

