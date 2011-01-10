package a11;

import java.util.Scanner;

public class Server {
    public static void main(String argv[]) {
        String port = "";
        System.out.printf("Bitte Server Port eingeben: ");
        Scanner s = new Scanner(port);
        s.next();
        System.in.read()
        RegisterServer rS = new RegisterServer(Integer.parseInt(port));
    }
}
