package a11;

public class StringTest {

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        char [] vocale = new char[]{'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};
        String clientSentence = "Hallo Du da. Wie geht es dir?";
        String s = clientSentence.toLowerCase();
        System.out.println("Substring: " + s.substring(0,3));
        char work;
        for(int i = 0; i < s.length(); i++){
            work = s.charAt(i);
            
            boolean match = false;
            for(int j = 0; j < vocale.length; j++){
                if(work == vocale[j]){
                    match = true;
                }
            }
            if(match){
                String sub1 = s.substring(0, i);
                String sub2 = s.charAt(i) + "o" + s.charAt(i);
                String sub3 = s.substring(i+1, s.length());
                s = sub1 + sub2 + sub3;
                i+=2;
            }
            
        }
        System.out.println("Ergebnis: " + s);

    }

}
