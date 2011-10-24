package a01v2;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 01<br>
 * 
 * Version: V2<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

public class BmiCalculator {

	private float value;
	
	public BmiCalculator() {
		this.value = 0;
	}
	
	public void calcBmi(float weigth, float height) throws NumberFormatException {
			if(weigth > 0 && height > 0) {
				this.value = weigth / (height * height);
			} else {
				throw new NumberFormatException();
			}		
	}
	
	public float show() {
		return this.value;
	}
}
