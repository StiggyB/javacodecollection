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
import static org.junit.Assert.assertEquals;
import org.junit.Test;

public class TextAnalyserTest {

	
	@Test
	public void testFindPalindrom() {
		TextAnalyser.text.add("Ein Neger mit Gazele zagt im regen nie.");
		TextAnalyser.findPalindrom();
		
		int i = 0;
		if (i < TextAnalyser.palindroms.size()) {
			assertEquals("Ein Neger mit Gazele zagt im regen nie.", TextAnalyser.palindroms
					.get(i++));
		}

		assertEquals("Ein Neger mit Gazele zagt im regen nie.", TextAnalyser
				.checkPalinSen(new StringBuilder("Ein Neger mit Gazele zagt im regen nie.")));
		assertEquals(
				"Die Liebe ist Sieger; stets rege ist sie bei Leid.",
				TextAnalyser
						.checkPalinSen(new StringBuilder(
								"Die Liebe ist Sieger; stets rege ist sie bei Leid.")));
		assertEquals("O Genie, der Herr ehre Dein Ego!", TextAnalyser
				.checkPalinSen(new StringBuilder(
						"O Genie, der Herr ehre Dein Ego!")));
		assertEquals("Trug Tim eine so helle Hose nie mit Gurt?",
				TextAnalyser.checkPalinSen(new StringBuilder(
						"Trug Tim eine so helle Hose nie mit Gurt?")));
	}
	@Test
	 public void testFindAnagram() {
	 assertEquals("HAENSEL UND GRETEL EHRT ENGLANDS EULE",
	 TextAnalyser.findAnagram(/*File file*/));
	 assertEquals("CHAOS ACH SO!", TextAnalyser.findAnagram(/*File file*/));
	 assertEquals("RENTENDISPUT SPINNERDUETT", TextAnalyser.findAnagram(/*File
	 file*/));
	 }
}
