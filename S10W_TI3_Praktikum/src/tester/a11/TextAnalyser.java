package tester.a11;
/**
 * Praktikum: P1P<br>
 * Semester: SS10<br>
 * Aufgaben-Nr.: 11<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen:
 * 
 * @author Mueller-Pettenpohl, Tell #1989982<br>
 */
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Pattern;

import javax.swing.JFileChooser;

public class TextAnalyser {

	static List<String> text = new ArrayList<String>();
	static List<String> palindroms = new ArrayList<String>();

	static int countWords(File input) throws FileNotFoundException {
		Scanner sc = new Scanner(input);
		int cnt = 0;
		while (sc.hasNext()) {
			text.add(sc.next());
			cnt++;
		}
		return cnt;
	}

	static int[] countChars(File file) throws IOException {
		BufferedReader fr = new BufferedReader(new FileReader(file));
		int[] cntArr = new int[3];
		int charCnt = 0;
		int consCnt = 1;
		int vowelCnt = 2;
		
		int ch = fr.read();
		while (ch != -1) {
			if (Character.isLetterOrDigit(ch)) {
				if (ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E'
						|| ch == 'i' || ch == 'I' || ch == 'o' || ch == 'O'
						|| ch == 'u' || ch == 'U') {
					cntArr[vowelCnt]++;
				} else {
					cntArr[consCnt]++;
				}
			}
			cntArr[charCnt]++;
			ch = fr.read();
		}
		return cntArr;
	}
	
	static void findPalindrom() {
		StringBuilder builder;
		StringBuilder senBuilder = new StringBuilder();

		for (int i = 0; i < text.size(); i++) {
			builder = new StringBuilder(text.get(i));
			String word = checkPalinWord(builder);
			if (word != null) {
				palindroms.add(word);
			}
			senBuilder.append(builder.toString());
			if (builder != null && builder.charAt(builder.length() -1) != '.') {
				senBuilder.append(" ");
			} else {
				String sentence = checkPalinSen(senBuilder);
				if (sentence != null) {
					palindroms.add(sentence);
				}
				senBuilder = new StringBuilder();
			}	
		}
	}

	static String checkPalinWord(StringBuilder word) {
		Pattern p = Pattern.compile("\\p{Punct}*", Pattern.CASE_INSENSITIVE);

		String palin1 = p.matcher(word.toString()).replaceAll("").toUpperCase();
		String palin2 = p.matcher(word.reverse().toString()).replaceAll("")
				.toUpperCase();
		if (palin1 != null && palin1.equals(palin2)) {
			return word.reverse().toString();
		} else {
			word.reverse();
			return null;
		}
	}

	static String checkPalinSen(StringBuilder senBuilder) {
		Pattern p = Pattern.compile("\\p{Space}*\\p{Punct}*",
				Pattern.CASE_INSENSITIVE);

		String sentence1 = p.matcher(senBuilder.toString()).replaceAll("")
				.toUpperCase();
		String sentence2 = p.matcher(senBuilder.reverse().toString())
				.replaceAll("").toUpperCase();
		if (sentence1.equals(sentence2)) {
			return senBuilder.reverse().toString();
		} else {
			senBuilder.reverse();
			return null;
		}
	}

	static String findAnagram() {
		return " ";
	}

	static void printText() {
		Collections.sort(text);
		System.out.println("Sorted:");
		for (String s : text) {
			System.out.println(s);
		}
	}

	static void printPalindroms() {
		Collections.sort(palindroms);
		System.out.println("Palindroms:");
		for (String s : palindroms) {
			System.out.println(s);
		}
	}

	public static void main(String[] args) {
		JFileChooser jfc = new JFileChooser();
		int rc = jfc.showOpenDialog(null);
		File file = new File(jfc.getSelectedFile().getName());

		if (rc == JFileChooser.APPROVE_OPTION) {
			System.out.println("You have choosn "
					+ jfc.getSelectedFile().getName());
		} 
		try {
			System.out.println(countWords(file) + " words have been read");
			int[] arr = countChars(file);
			System.out.println(arr[0] + " chars include the analysed text.");
			System.out.println(arr[1]
					+ " consonants include the analysed text.");
			System.out.println(arr[2] + " vowels include the analysed text.\n");

			findPalindrom();
			printPalindroms();
			
			File file1 = new File("./test");
			if (file1.mkdir()) {
				System.out.println(file1.getName() + " created.");
			}
			rc = jfc.showSaveDialog(null);
			if (rc == JFileChooser.APPROVE_OPTION) {
				
				if (jfc.getSelectedFile().createNewFile()) {
					System.out.println(jfc.getSelectedFile().getName() + " created.");
				
					PrintWriter pw =
						new PrintWriter (
						new BufferedWriter ( new OutputStreamWriter (
						new FileOutputStream(jfc.getSelectedFile()))));
					for (Iterator<String> it = text.iterator(); it.hasNext();) {
						pw.print((String) it.next()); 
						pw.println();
					} 
					pw.flush(); 
					pw.close();
					
//				ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream(jfc.getSelectedFile()));
//				os.writeObject(file.toString());
//				os.close();

				System.out.println("You have saved " + file.getName());
				}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
