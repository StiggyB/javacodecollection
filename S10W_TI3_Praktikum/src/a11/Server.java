package a11;

import java.io.IOException;
import java.util.Scanner;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;


public class Server {
    public static void main(String argv[]) throws IOException {
        System.out.printf("Bitte Server Port eingeben: ");
        Scanner sc= new Scanner(System.in);
        int port = sc.nextInt();
        ThreadPoolExecutor threadPool;
        int poolSize = Constants.MAXCLIENTS;
        int maxPoolSize = Constants.MAXCLIENTS*2;
        long keepAliveTime = 10;
        final ArrayBlockingQueue<Runnable> queue = new ArrayBlockingQueue<Runnable>(Constants.MAXCLIENTS);
        threadPool = new ThreadPoolExecutor(poolSize, maxPoolSize, keepAliveTime, TimeUnit.SECONDS, queue);
        RegisterServer rS = new RegisterServer(port, threadPool);
        threadPool.submit(rS);
    }
}
