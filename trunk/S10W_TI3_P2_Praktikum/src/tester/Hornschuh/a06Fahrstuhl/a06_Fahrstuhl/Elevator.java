package tester.Hornschuh.a06Fahrstuhl.a06_Fahrstuhl;

import java.util.Queue;

import a05.RingBuffer;


public class Elevator extends Thread {
    
    
    // _________________________________________________________________________
    // Declarations

    private int no;                     // number of the elevator
    private int pos = 0;                // current position
    private RingBuffer<Integer> targets;     // target floors
    private boolean run = true;         // flag for thread termination (not yet used)
    private Facility facility;          // access to the GUI
    
    
    // _________________________________________________________________________
    // Constructors
    
    public Elevator( int no, Facility facility ) {
        this.no = no;
        this.facility = facility;
        targets = new RingBuffer<Integer>( Constants.FLOORCOUNT );
    }

    
    // _________________________________________________________________________
    // Methods
    
    public synchronized int insertTarget( int target ) {
        return targets.enqueue( target );
    }
    
    public int getPos() {
        return pos;
    }
    
    public synchronized boolean isIdle() {
        return targets.isEmpty();
    }
    
    private synchronized void sleep( int time ) {
        try {
            wait( time );
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    
    private synchronized void moveToFloor( int target ) {
        // move to floor if not already there
        if( pos != target ) {
            // calculate direction and floors to pass
            int nof;                    // number of floors
            int direction = 0;          // up or down
            if( target > pos ) {
                direction = 1;          // up
                nof = target - pos;
            } else {
                direction = -1;         // down
                nof = pos - target;
            }
            
            // move to the target floor, on the way update the GUI images
            for( int i=1; i<=nof; i++ ) {
                sleep( Constants.VELOCITY );
                facility.setIconToNo(pos, no);
                pos += direction;
                facility.setIconToClosed(pos, no);
            }
        }
        
        // wait some time then open the doors
        sleep(1000);
        facility.setIconToOpened(pos, no);
        
        // stay on floor for configured holdtime then close the doors
        sleep( Constants.HOLDTIME );        
        facility.setIconToClosed(pos, no);
    }

    /**
     * drive to the targets in the queue or stay at position
     */
    @Override
    public void run() {
        while( run ) {
            if( targets.isEmpty() ) {
                sleep( 200 );
                continue;
            }
            moveToFloor( targets.peek() );
            targets.dequeue();
        }
    }
    
}
