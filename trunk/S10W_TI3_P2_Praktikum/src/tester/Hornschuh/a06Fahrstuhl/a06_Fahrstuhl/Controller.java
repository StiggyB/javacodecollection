package tester.Hornschuh.a06Fahrstuhl.a06_Fahrstuhl;

/**
 * @author Jonas Hornschuh, Behzad Mahmoudi
 *
 */

import java.util.LinkedList;
import java.util.Random;

public class Controller extends Thread {

    
    // _________________________________________________________________________
    // Declarations
    

    private Elevator[] elevators;          // elevator threads
    private LinkedList<Integer> targets;   // target floors
    private boolean run = true;            // flag for thread termination (not yet used)
    Facility facility;                     // GUI representation
    
    
    // _________________________________________________________________________
    // Constructors
    
    public Controller() {
        elevators = new Elevator[ Constants.ELEVATORCOUNT ];
        targets = new LinkedList<Integer>();
        facility = new Facility( this );
        initiate();
    }
    
    
    // _________________________________________________________________________
    // Methods

    /**
     * create elevator threads and start them
     */
    private void initiate() {
        for( int i=0; i<Constants.ELEVATORCOUNT; i++ ) {
            elevators[i] = new Elevator( i, facility );
            elevators[i].start();
        }
    }
    
    
    /**
     * add targets to linked list
     */
    public synchronized void addTarget( int target ){
        targets.add( target );
    }


    /**
     * Delegate targets to the elevators
     * 
     * Checks the state of the elevators starting with the first. If an
     * elevator is idle, delegate the target to this elevator. If all
     * elevators are busy, delegate the target to a random selected elevator.
     */
    @Override
    public void run() {
        while( run ) {
            if( targets.isEmpty() ) {
                try {
                    synchronized(this) {
                        this.wait( 200 );
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                continue;
            }
            
            int elevator = 0;
            while( true ) {
                System.out.println("Liste: " + targets.size());
                if( elevators[elevator].isIdle() ) {
                    // delegate target only if elevators queue is not full
                    if( elevators[elevator].insertTarget( targets.getFirst() ) == 0 ) {
                        targets.removeFirst();
                        break;
                    }
                } else if( elevator < Constants.ELEVATORCOUNT-1 ) {
                    elevator++;
                    continue;
                } else {
                    Random g = new Random();
                    elevator = g.nextInt( Constants.ELEVATORCOUNT );
                    // delegate target only if elevators queue is not full
                    if( elevators[elevator].insertTarget( targets.getFirst() ) == 0 ) {
                        targets.removeFirst();
                        break;
                    }
                }
            }
        }
    }
    
    
    // _________________________________________________________________________
    // MAIN method
    
    public static void main(String[] args) {
        Controller controller = new Controller();
        controller.start();
    }

}
